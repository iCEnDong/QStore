#if 0
#include "v4l2_camera.h"
#include "ui_v4l2camera.h"
#include "order_menu.h"
#include <QZXing>

V4L2Camera::V4L2Camera(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::V4L2Camera)
{
    ui->setupUi(this);

    if(V4L2Camera_Init()) {
        qDebug() << "success.";
        timer = new QTimer(this);
        timer->setInterval(50);
        connect(timer, &QTimer::timeout, this, &V4L2Camera::show_carema_to_video);
        timer->start();
    }else {
        qDebug() << "Init..Falied";
    }
}

void Close_Fd(int fd) {
    if(fd != -1)
        close(fd);
}
V4L2Camera::~V4L2Camera()
{
    delete ui;
    Close_Fd(getFd());
    // 释放 v_mmap_start 中的动态分配内存
    for(int i = 0;i < reqbuf.count;i++) {
        munmap(v_mmap_start[i], buffer[i].length);
    }

    // 清空 QVector
    v_mmap_start.clear();
    buffer.clear();
}

bool V4L2Camera::V4L2Camera_Init() {
    /* 打开设备文件并映射屏幕 */
    this->fd_video = open("/dev/video7", O_RDWR);

    if(fd_video == -1) {
        qDebug() << "fd_video..";
        return false;
    }

    /* 获取摄像头参数和设置其格式 */
    memset(&format, 0, sizeof(format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd_video, VIDIOC_G_FMT, &format) == -1) {
        qDebug() << "ioctl..VIDIOC_G_FMT..";
        return false;
    }

    // 打印信息
    qDebug() << "宽度: "  << format.fmt.pix.width;
    qDebug() << "高度: " <<  format.fmt.pix.height;

    if (format.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV) {
        qDebug() << "摄像头像素格式为YUYV\n";
    } else if (format.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG) {
        qDebug() << "摄像头像素格式为JPEG\n";
    }

    /* 申请缓存区 */
    memset(&reqbuf, 0, sizeof(reqbuf));
    reqbuf.count = 3;
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(fd_video, VIDIOC_REQBUFS, &reqbuf) == -1) {
        qDebug() << "ioctl..VIDIOC_REQBUFS..";
        return false;
    }

    /* 映射缓存区 */
    for(int index = 0;index < reqbuf.count;index++) {
        // 查询
        struct v4l2_buffer t_buffer;
        memset(&t_buffer, 0, sizeof(struct v4l2_buffer));
        t_buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        t_buffer.memory = V4L2_MEMORY_MMAP;
        t_buffer.index = index;

        // 获取对应缓存区信息
        if(ioctl(fd_video, VIDIOC_QUERYBUF, &t_buffer) == -1) {
            qDebug() << "ioctl..VIDIOC_QBUF";
            return false;
        }
        buffer.push_back(t_buffer);

        unsigned char * t_mmap =
            (unsigned char *)mmap(NULL, buffer[index].length, PROT_READ | PROT_WRITE,
                                   MAP_SHARED, fd_video, buffer[index].m.offset);
        if (t_mmap == MAP_FAILED) {
            qDebug() << "mmap...";
            return false;
        }
        v_mmap_start.push_back(t_mmap);

        // 将申请的缓存区设置为存放图像的队列
        if (ioctl(fd_video, VIDIOC_QBUF, &buffer[index]) == -1) {
            qDebug() << "ioctl..VIDIOC_QBUF..";
            return false;
        }
    }
    /* 轮询,通过三个缓存区的首地址获取每一帧监控换面并映射到屏幕上 */
    this->vtype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd_video, VIDIOC_STREAMON, &vtype) == -1) {
        qDebug() << "ioctl..VIDIOC_STREAMON..";
        return false;
    }

    // 轮询拿到
    memset(&vbuf, 0, sizeof(vbuf));
    this->vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vbuf.memory = V4L2_MEMORY_MMAP;

    return true;
}

void V4L2Camera::YUYVtoRGB(int i, unsigned char *rgbData) {
    const unsigned char *yuyvData = v_mmap_start[i];
    int imageSize = format.fmt.pix.width * format.fmt.pix.height * 2;
    int rgbIndex = 0;

    for (int i = 0; i < imageSize; i += 4) {
        unsigned char y0 = yuyvData[i];     // 当前像素的亮度分量
        unsigned char u = yuyvData[i + 1];  // 当前像素的色度分量（U）
        unsigned char y1 = yuyvData[i + 2]; // 下一个像素的亮度分量
        unsigned char v = yuyvData[i + 3];  // 下一个像素的色度分量（V）

        int c = (int)y0 - 16; // 调整亮度分量的范围
        int d = (int)u - 128; // 调整色度分量的范围
        int e = (int)v - 128; // 调整色度分量的范围

        int r = (298 * c + 409 * e + 128) >> 8;           // 计算红色分量
        int g = (298 * c - 100 * d - 208 * e + 128) >> 8; // 计算绿色分量
        int b = (298 * c + 516 * d + 128) >> 8;           // 计算蓝色分量

        // 将RGB分量的值限制在合法范围内（0-255）
        r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
        g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
        b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

        // 存储转换后的RGB分量值到输出缓冲区
        rgbData[rgbIndex++] = (unsigned char)r;
        rgbData[rgbIndex++] = (unsigned char)g;
        rgbData[rgbIndex++] = (unsigned char)b;

        c = (int)y1 - 16; // 调整亮度分量的范围

        r = (298 * c + 409 * e + 128) >> 8;           // 计算红色分量
        g = (298 * c - 100 * d - 208 * e + 128) >> 8; // 计算绿色分量
        b = (298 * c + 516 * d + 128) >> 8;           // 计算蓝色分量

        r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
        g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
        b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

        rgbData[rgbIndex++] = (unsigned char)r;
        rgbData[rgbIndex++] = (unsigned char)g;
        rgbData[rgbIndex++] = (unsigned char)b;
    }
}

void V4L2Camera::call_show(unsigned char *rgbData) {
    int width = 640, height = 480;
    // 创建 QImage 对象，格式设置为 ARGB32
    QImage image(rgbData, width, height, QImage::Format_RGB888);

    // 使用 QZXing 解码图像
    QZXing decoder;
    QString decodedText = decoder.decodeImage(image);

    // 读取到内容
    if (!decodedText.isEmpty()) {
        qDebug() << "text: " << decodedText;
        this->finish = true;
        this->account = decodedText;
    }

    // 填充 QImage 数据
    for (int y = 0, n = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, n += 3) {
            image.setPixel(x, y, qRgb(rgbData[n], rgbData[n + 1], rgbData[n + 2]));
        }
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_screen->setPixmap(pixmap);
}

void V4L2Camera::show_carema_to_video() {
    unsigned char rgb[format.fmt.pix.width * format.fmt.pix.height * 3];

    for(int i = 0;i < 3;i++) {
        vbuf.index = i;
        if(ioctl(fd_video, VIDIOC_DQBUF, &vbuf) == -1) {
            qDebug() << "ioctl..VIDIOC_DQBUF";
            return;
        }

        // yuyv转rgb
        YUYVtoRGB(i, rgb);
        // 显示rgb图片
        call_show(rgb);
        // 归还缓存区
        ioctl(fd_video, VIDIOC_QBUF, &vbuf);
    }
    if(finish) {
        OrderMenu * orderMenu = (OrderMenu *)(this->parent());
        emit orderMenu->send_order_signal(this->account);
        on_pBtn_close_clicked();
    }
}

void V4L2Camera::on_pBtn_close_clicked()
{
    this->close();
    delete this;
}

#endif
