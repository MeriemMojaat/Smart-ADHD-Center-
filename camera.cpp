#include "camera.h"
#include "ui_camera.h"
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>

Camera::Camera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);

    //Camera devices:
    setCamera(QCameraInfo::defaultCamera());
}

Camera::~Camera()
{
    delete ui;
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(camera);
    camera->setViewfinder(ui->viewfinder);
    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &Camera::readyForCapture);
    camera->start();
}


void Camera::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}

void Camera::on_takeImageButton_clicked()
{
    isCapturingImage = true;
    imageCapture->capture();
}

