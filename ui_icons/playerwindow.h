#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playerframe.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLayout>
#include <QSlider>


namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();

private:
    void SetTimeLabel();

private slots:

    void on_BtnPlay_clicked();

    void on_BtnPause_clicked();

    void on_BtnStop_clicked();

    void on_comboBox_activated(int index);

    void on_directory_clicked();

    void GetFrame(QPixmap pix);

    void on_vSliderSound_valueChanged(int value);

    void on_hSliderVideo_sliderMoved(int position);

    void on_actionAdd_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_actionExit_triggered();

    void on_actionInfo_triggered();

    void on_BtnMute_clicked();



Q_SIGNALS:
    void fnClearPixmap();

private:

    Ui::PlayerWindow *ui;
    QVideoWidget *videoWidget;
    QMediaPlayer *mediaPlayer;
    QSlider *slider;
    QVBoxLayout *layout;
    QMediaPlayer player;
    PlayerFrame *pFrame;
    QPixmap pixmap;
    int fileCounter = 0;
    QString filename;

};

#endif // MAINWINDOW_H

