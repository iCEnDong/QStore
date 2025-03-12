#ifndef V4L2_CAMERA_H
#define V4L2_CAMERA_H

#if 0
#include <QMainWindow>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QObject>


extern "C" {
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
}

namespace Ui {
class V4L2Camera;
}

class V4L2Camera : public QMainWindow
{
    Q_OBJECT

public:
    explicit V4L2Camera(QWidget *parent = nullptr);
    ~V4L2Camera();
    bool V4L2Camera_Init();
    void YUYVtoRGB(int i, unsigned char *rgb);
    void call_show(unsigned char * rgbData);
    int getFd(){return fd_video;}

private slots:
    void show_carema_to_video();
    void on_pBtn_close_clicked();

private:
    Ui::V4L2Camera *ui;

    int fd_video;
    struct v4l2_format format;
    struct v4l2_requestbuffers reqbuf;
    QVector <struct v4l2_buffer> buffer;
    QVector <unsigned char *> v_mmap_start;
    enum v4l2_buf_type vtype;
    struct v4l2_buffer vbuf;
    QTimer *timer;
    QString account;
    bool finish =false;
};
#endif

#endif // V4L2_CAMERA_H
