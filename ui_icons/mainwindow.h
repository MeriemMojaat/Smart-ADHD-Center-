#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableView>
#include<QSqlQueryModel>
#include <QtWidgets>
#include <QAbstractItemModel>
#include<QSqlQuery>
#include<QTableWidget>
#include "resource.h"
#include <QPieSeries>
#include "smtp.h"
#include <QMainWindow>
#include "playerframe.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLayout>
#include <QSlider>
#include "arduino.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#define nullptr NULL


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetTimeLabel();

private slots:
   // void on_pushButton_create_clicked();

    void on_pushButton_add_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_delete_clicked();

    void on_comboBox_sort_activated();
    void on_lineEdit_recherche_cursorPositionChanged();

    void on_pushButton_PDF_clicked();

    void on_pushButton_7_clicked();
    //mailling
    void sendMail();
    void mailSent(QString);
    void browse();

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
    Ui::MainWindow *ui;
    QStringList files;
    resource R;

    Arduino A;

    QVideoWidget *videoWidget;
    QMediaPlayer *mediaPlayer;
    QSlider *slider;
    QVBoxLayout *layout;
    QMediaPlayer player;
    PlayerFrame *pFrame;
    QPixmap pixmap;
    int fileCounter = 0;
    QString filename;
private slots:
    void runLoop() {
        QString value = A.read_from_arduino2(); // assuming A is an instance of your Arduino object


        if (!value.isEmpty()) {
            ui->arduinoo->setText(value);

        // Execute the query to check if the value is present in the database
        QSqlQuery query;
        query.prepare("SELECT TITLE FROM RESSOURCE_LIBRARY WHERE TITLE = :TITLE");
        query.bindValue(":TITLE", value);
        if (query.exec() && query.next()) {
            // If the value is found, send the name of the person to the Arduino
            QString name = query.value(0).toString();
            QByteArray data = name.toUtf8();
            A.write_to_arduino(data);
        } else {
            // If the value is not found, send "not found" to the Arduino
            QByteArray data = "not found";
            A.write_to_arduino(data);
        }
    }
}
 //   void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
