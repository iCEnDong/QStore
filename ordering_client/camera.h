#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraDevice>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QVideoWidget>

namespace Ui {
class Camera;
}

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();
    void openCamera(QVideoWidget *showWidget);

private:
    Ui::Camera *ui;

    QCamera * camera;
    QVideoWidget * showWidget;
};

#endif // CAMERA_H
