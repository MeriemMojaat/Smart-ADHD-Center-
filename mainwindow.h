#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employee.h"
#include "patient.h"
#include "treatment.h"
#include "arduino.h"
#include "appointment.h"
#include "resource.h"
#include "event.h"
#include "smtp.h"
#include "camera.h"

#include "playerframe.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QLayout>
#include <QSlider>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMainWindow>
#include <QPdfWriter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyledItemDelegate>
#include <Qt>
#include <QObject>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

#define nullptr NULL
namespace Ui {
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
    //MINOU
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_update_clicked();
    void on_comboBox_sort_activated();
    void on_lineEdit_recherche_cursorPositionChanged();
    void on_pushButton_PDF_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    //DONIA

    void on_pushButton_create_clicked();
    void on_pushButton_deletep_clicked();
    void on_pushButton_updatep_clicked();

    void on_comboBox_sortp_activated();
    void on_lineEdit_recherchep_cursorPositionChanged();

    void on_pushButton_PDFp_clicked();
    void on_pushButton_statchartp_clicked();
    void on_pushButton_stattextp_clicked();
    void showTime();
    void on_btn_image_clicked();

    void updatep_label();
    int control_idpp(int id_patient);
    int control_type(QString type);
    void on_pushButton_arduinop_clicked();

//Meriem

    void on_pushButton_Add_clicked();
    void on_pushButton_Delete_clicked();
    void on_pushButton_updatet_clicked();
    void cleart_form();

    void on_comboBox_sortt_activated();

    void on_lineEdit_recherchet_cursorPositionChanged();

    void on_pushButton_PDFt_clicked();

    void on_pushButton_QRcode_clicked();

    void on_pushButton_sms_clicked();
    void onSMSResponse(QNetworkReply *reply);
    void sendSMS(QString fromNumber, QString toNumber, QString apiKey, QString apiSecret, QString message);

    void on_pushButton_statchartt_clicked();
    void on_pushButton_stattextt_clicked();

    void on_pushButton_whatsapp_clicked();

    void updatet_label();


    //Jawher

    void on_pushButton_Adda_clicked();
    void on_pushButton_Deletea_clicked();
    void on_pushButton_updatea_clicked();

    void on_pushButton_excel_clicked();

    void refresh();

    void on_lineEdit_recherchea_cursorPositionChanged();
    void on_comboBox_sorta_activated();
    void on_pushButton_PDFa_clicked();
    void on_pushButton_statcharta_clicked();
    void on_pushButton_stattexta_clicked();

    void cleara_form();

    //Nour

    void on_pushButton_createe_clicked();
    void on_pushButton_deletee_clicked();
    void on_pushButton_updatee_clicked();

    void on_comboBox_sorte_activated();
    void on_lineEdit_recherchee_cursorPositionChanged();
    void on_pushButton_PDFe_clicked();
    void on_pushButton_statcharte_clicked();
    void on_pushButton_stattexte_clicked();
    bool get_volunteer_info();
    void on_camera_clicked();

   /* void updatee_label();
    int controle_idp(int id_patient);
    void on_pushButton_arduinoe_clicked();*/

    //Anas
    void on_pushButton_addr_clicked();
    void on_pushButton_updater_clicked();
    void on_pushButton_deleter_clicked();

    void on_comboBox_sortr_activated();
    void on_lineEdit_rechercher_cursorPositionChanged();

    void on_pushButton_PDFr_clicked();

    void on_pushButton_7r_clicked();
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

    Employee E;
    Arduino A;
    patient p ;
    Treatment T;
    Appointment Ap;
    class event e;
    Camera *c;
    QStringList files;
    resource R;
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
            ui->lineEdit_IDCARD->setText(value);
        // Execute the query to check if the value is present in the database
        QSqlQuery query;
        query.prepare("SELECT EFIRST_NAME FROM EMPLOYEE WHERE IDCARD = :IDCARD");
        query.bindValue(":IDCARD", value);
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

void on_pushButton_add_2_clicked();

};



#endif // MAINWINDOW_H
