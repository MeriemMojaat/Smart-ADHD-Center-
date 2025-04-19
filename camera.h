#ifndef CAMERA_H
#define CAMERA_H
#include <QDialog>
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QtMultimedia>

#include <QPalette>


namespace Ui {
class Camera;
}

class Camera : public QDialog
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();

private slots:
    void setCamera(const QCameraInfo &cameraInfo);
    void readyForCapture(bool ready);

    void on_takeImageButton_clicked();

private:
    Ui::Camera *ui;
    QCamera *camera = nullptr;
    QCameraImageCapture *imageCapture = nullptr;
    QMediaRecorder* mediaRecorder = nullptr;

    QImageEncoderSettings imageSettings;
    QAudioEncoderSettings audioSettings;
    QVideoEncoderSettings videoSettings;
    QString videoContainerFormat;
    bool isCapturingImage = false;
    bool applicationExiting = false;
};

#endif // CAMERA_H

