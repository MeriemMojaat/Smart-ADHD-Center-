#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resource.h"
#include <QMessageBox>
#include <QComboBox>
#include <QPieSeries>
#include <QtCharts>
#include "playerwindow.h"
#include <string>
#include <QFileDialog>
#include <string>
#include <QFileDialog>
#include <QDialog>
#include <QTimer>
#include "arduino.h"

using std::to_string;
using std::string;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(R.Read());
    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    layout = new QVBoxLayout();

    layout->addWidget(videoWidget);
    ui->groupBox_2->setLayout(layout);
    mediaPlayer->setVideoOutput(videoWidget);
    ui->directory->setIcon(QIcon(":/Resources/ui_icons/Add File.png"));

    connect(mediaPlayer, &QMediaPlayer::durationChanged, ui->hSliderVideo, &QSlider::setMaximum);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, ui->hSliderVideo, &QSlider::setValue);


    this->on_vSliderSound_valueChanged(50);

    pFrame = new PlayerFrame();
    player.setVideoOutput(pFrame);
    int ret=A.connect_arduino(); // launch the connection to arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    QTimer *timer = new QTimer(this);
           connect(timer, SIGNAL(timeout()), this, SLOT(runLoop()));

           timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pFrame;
    delete mediaPlayer;
    delete layout;
    delete videoWidget;
    delete ui;
}


void MainWindow::on_pushButton_update_clicked()
{
    // Get information entered in the 3 fields
    int ID_RESSOURCE = ui->res->text().toInt();
    QString TITLE = ui->TITLE->text();
    QString RLANGUAGE = ui->RLANGUAGE->text();
    QString RTYPE = ui->RTYPE->text();
    QString RAVAILIBILITY = ui->RAVAILIBILITY->text();
    QDate RDATE = ui->RDATE->date();
    QString RDESCRIPTION = ui->RDESCRIPTION->text();
    int ID_EMPLOYEE = ui->ID_EMPLOYEE->text().toInt();


         resource R(ID_RESSOURCE, TITLE, RLANGUAGE, RTYPE, RAVAILIBILITY, RDATE, RDESCRIPTION, ID_EMPLOYEE);

                       bool test =R.Update();
                       if(test )
                       {
                           QMessageBox::information(nullptr, QObject::tr("database is open"),
                                       QObject::tr("update successful.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
     ui-> tableView->setModel(R.Read());


                       }
                       else{
                           QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                       QObject::tr("update failed.\n"

                                         "Click Cancel to exit."), QMessageBox::Cancel);}

   }






void MainWindow::on_pushButton_add_clicked()//add
{
    // Get information entered in the 3 fields
    int ID_RESSOURCE = ui->res->text().toInt();
    QString TITLE = ui->TITLE->text();
    QString RLANGUAGE = ui->RLANGUAGE->text();
    QString RTYPE = ui->RTYPE->text();
    QString RAVAILIBILITY = ui->RAVAILIBILITY->text();
    QDate RDATE = ui->RDATE->date();
    QString RDESCRIPTION = ui->RDESCRIPTION->text();
    int ID_EMPLOYEE = ui->ID_EMPLOYEE->text().toInt();

    resource R(ID_RESSOURCE, TITLE, RLANGUAGE, RTYPE, RAVAILIBILITY, RDATE, RDESCRIPTION, ID_EMPLOYEE); // object instantiation
                                          // using information entered in the interface

    bool test = R.Create(); // insert the object into the database resource table
                            // and get the returned value of query.exec()

    if (test) // if the query is executed  ==> QMessageBox::information
    {
        // Refresh
        ui->tableView->setModel(R.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Insert done \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else // if the query is not executed  ==> QMessageBox::critical
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Insert failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_delete_clicked() //delete
{
    int ID_RESSOURCE =ui->del->text().toInt();//khdina l id li bech nfasskhouha
    bool test=R.Delete(ID_RESSOURCE);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableView->setModel(R.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

//sort
void MainWindow::on_comboBox_sort_activated()
{
    if(ui->comboBox_sort->currentText()=="Language")
           {
               ui->tableView->setModel(R.sortlanguage());

           }else if(ui->comboBox_sort->currentText()=="Availability")
           {
               ui->tableView->setModel(R.sortavailability());

           }else
           {
               ui->tableView->setModel(R.sorttype());
           }
}

//search

void MainWindow::on_lineEdit_recherche_cursorPositionChanged()
{
    QString rech=ui->lineEdit_recherche->text();
        ui->tableView->setModel(R.recherche(rech));

}

void MainWindow::on_pushButton_PDF_clicked()
{
    QPdfWriter pdf("C:\\Users\\HP\\Documents\\CRUD\\PDF_ressource.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"List of Ressource Library");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(300,3300,"Id Ressource");
                 painter.drawText(1300,4300,"Title");
                 painter.drawText(2300,3300,"Language");
                 painter.drawText(3500,3300,"Type");
                 painter.drawText(4600,3300,"Availability");
                 painter.drawText(6000,3300,"Date");
                 painter.drawText(6000,3300,"Description");
                 painter.drawText(8000,3300,"Id Employee");
                 painter.drawRect(100,3000,9400,10700);

                 QSqlQuery query;
                 query.prepare("SELECT * FROM RESSOURCE_LIBRARY");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1300,i,query.value(1).toString());
                     painter.drawText(2300,i,query.value(2).toString());
                     painter.drawText(3900,i,query.value(3).toString());
                     painter.drawText(5700,i,query.value(4).toString());
                     painter.drawText(7100,i,query.value(5).toString());
                     painter.drawText(8100,i,query.value(6).toString());
                     painter.drawText(8900,i,query.value(7).toString());
                    i = i + 350;
                 }
                 QMessageBox::information(this, QObject::tr("PDF Downloaded !"),
                 QObject::tr("PDF Downloaded ! \n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_7_clicked()
{
    //stat

            // Query the database to get the number of active and pending collaborators
            QSqlQuery query;
            query.prepare("SELECT COUNT(*) FROM resource WHERE RTYPE = 'Book'");
            query.exec();
            query.next();
            int BookCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM resource WHERE RTYPE = 'Article'");
            query.exec();
            query.next();
            int ArticleCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM resource WHERE RTYPE = 'Magazine'");
            query.exec();
            query.next();
            int MagazineCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM resource WHERE RTYPE = 'Online'");
            query.exec();
            query.next();
            int OnlineCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM resource WHERE RTYPE = 'Retailer'");
            query.exec();
            query.next();
            int RetailerCount = query.value(0).toInt();



            // Create a pie series and add the data to it
            QPieSeries *series = new QPieSeries();
            series->append("Book", BookCount);
            series->append("Article", ArticleCount);
            series->append("Magazine", MagazineCount);
            series->append("Online", OnlineCount);
            series->append("Retailer", RetailerCount);



            // Create a chart and add the series to it
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("resource RTYPE");

            // Create a chart view and set the chart as its model
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            // Create a dialog to display the chart view
            QDialog *dialog = new QDialog(this);
            dialog->setWindowTitle("resource RTYPE");
            dialog->resize(400, 300);
            QVBoxLayout *layout = new QVBoxLayout(dialog);
            layout->addWidget(chartView);

            // Show the dialog
            dialog->exec();
}
//mailing
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("anas.ganedi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("anas.ganedi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("anas.ganedi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}



void MainWindow::on_BtnPlay_clicked()
{
    mediaPlayer->play();
    if(!filename.isEmpty()){
        videoWidget->resize(videoWidget->width()+1, videoWidget->height());
        videoWidget->resize(videoWidget->width()-1, videoWidget->height());

    }
    this->SetTimeLabel();

}

void MainWindow::on_BtnPause_clicked()
{
    mediaPlayer->pause();
    this->SetTimeLabel();
}

void MainWindow::on_BtnStop_clicked()
{
    mediaPlayer->stop();
    this->SetTimeLabel();
}

void MainWindow::on_comboBox_activated(int rate)
{
    qreal nowrate = 0;
    switch (rate) {
        case 0:
        {
            nowrate = 1;
            break;
        }
    case 1:
        {
            nowrate = 0.5;
            break;
        }
    case 2:
        {
            nowrate = 2;
            break;
        }
    }
        mediaPlayer->setPlaybackRate(nowrate);
}

void MainWindow::on_directory_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose videofile..","","*.mp4;*.mp3");
    QFile f(path);
    QFileInfo fileInfo(f.fileName());
    QString filename = fileInfo.fileName();

    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    ui->LblNowPlaying->setText(""+filename);

    player.setMedia(QUrl::fromLocalFile(path));

    connect(pFrame, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(GetFrame(QPixmap)),Qt::QueuedConnection);

    connect(this, SIGNAL(fnClearPixmap()),
            pFrame, SLOT(fnClearPixmap()),Qt::QueuedConnection);

}

void MainWindow::GetFrame(QPixmap pix)
{
    player.pause();
    pixmap = pix;
}

void MainWindow::SetTimeLabel()
{
    int seconds = static_cast<int>(mediaPlayer->duration()/1000);
    int minutes = 0, hours = 0;
    string stringData;

    if (hours > 9){
        stringData = to_string(hours) + ":";
    }else{
        stringData = to_string(hours) + "0:";
    }

    if((minutes = seconds / 60) > 0){
        seconds -= minutes * 60;
        if((hours = minutes / 60) > 0){
            minutes -= hours * 60;
        }
    }
    if(minutes > 9){
         stringData += to_string(minutes) + ":";
    }else{
        stringData += "0" + to_string(minutes) + ":";
    }
    if(seconds > 9){
         stringData += to_string(seconds);
    }else{
        stringData += "0" + to_string(seconds);
    }
    ui->endTime->setText(QString::fromStdString(stringData));

}

void MainWindow::on_vSliderSound_valueChanged(int value)
{
    mediaPlayer->setVolume(value);
    if(value == 0){
        ui->BtnMute->setIcon(QIcon(":/Resources/ui_icons/Mute_48px.png"));
    }else{
        ui->BtnMute->setIcon(QIcon(":/Resources/ui_icons/Voice_48px.png"));
    }
    ui->vSliderSound->setSliderPosition(value);
}

void MainWindow::on_hSliderVideo_sliderMoved(int position)
{
    qInfo() << "position is " << position ;
    mediaPlayer->setPosition(position);
}

void MainWindow::on_actionAdd_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose your file.","","*.mp4;*.mp3");
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    ui->LblNowPlaying->setText(""+path);

    player.setMedia(QUrl::fromLocalFile(path));

    connect(pFrame, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(GetFrame(QPixmap)),Qt::QueuedConnection);

    connect(this, SIGNAL(fnClearPixmap()),
            pFrame, SLOT(fnClearPixmap()),Qt::QueuedConnection);
}

void MainWindow::on_actionPlay_triggered()
{
    mediaPlayer->play();
    videoWidget->resize(videoWidget->width()+1, videoWidget->height());
    videoWidget->resize(videoWidget->width()-1, videoWidget->height());
    this->SetTimeLabel();
}

void MainWindow::on_actionPause_triggered()
{
    mediaPlayer->pause();
}

void MainWindow::on_actionStop_triggered()
{
    mediaPlayer->stop();
    this->SetTimeLabel();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox mssInfo;
    mssInfo.setIcon(QMessageBox::Information);
    mssInfo.setText("This media player is developed by Harsha Madhushan Jayasinghe."
                    "This media player is support MP4 video files & mp3 audio files only."
                    "To work with the media player it is required to install codec software.");
    mssInfo.exec();
}

void MainWindow::on_BtnMute_clicked()
{
    mediaPlayer->setVolume(0);
    ui->vSliderSound->setSliderPosition(0);
}






/*void MainWindow::on_pushButton_clicked()
{
    QString value = A.read_from_arduino2(); // assuming A is an instance of your Arduino object
        ui->arduinoo->setText(value);

            // Execute the query to check if the value is present in the database
            QSqlQuery query;
            query.prepare("SELECT FIRST_NAME FROM collaborator WHERE Institution = :Institution");
            query.bindValue(":Institution", value);
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

}*/
