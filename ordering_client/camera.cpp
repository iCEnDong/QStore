#include "camera.h"
#include "ui_camera.h"

Camera::Camera(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Camera)
{
    ui->setupUi(this);
    showWidget = new QVideoWidget;
    ui->verticalLayout->addWidget(showWidget);
    openCamera(showWidget);
}

Camera::~Camera()
{
    delete ui;
}

// 打开摄像头
void Camera::openCamera(QVideoWidget *showWidget) {
    this->camera = new QCamera(QMediaDevices::defaultVideoInput());
    QMediaCaptureSession * videoSession = new QMediaCaptureSession;
    videoSession->setCamera(this->camera);
    videoSession->setVideoOutput(showWidget);
    this->camera->start();
}
