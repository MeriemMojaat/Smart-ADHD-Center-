#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "patient.h"
#include "arduino.h"
#include "treatment.h"
#include "appointment.h"
#include "resource.h"
#include "playerframe.h"
#include "event.h"
#include "smtp.h"
#include "excel.h"
#include "qrcode.h"
#include "authentication.h"
#include "widget.h"
#include "webaxwidget.h"
#include "camera.h"
#include <QTimer>
#include <QMessageBox>
#include <QSqlDatabase>
#include<QDir>
#include <QPdfWriter>
#include <QPainter>
#include <QPieSeries>
#include <QChartView>
#include <QTimer>
#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPixmap>

#include <QtCore>
#include <QtNetwork>
#include <QCryptographicHash>
#include <QSslSocket>
#include <QUrl>

using std::to_string;
using std::string;

using namespace DuarteCorporation;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(E.Read());
    ui->tableViewp->setModel(p.Read());
    ui->tableViewt->setModel(T.Read());
    ui->tableViewa->setModel(Ap.Read());
    ui->tableViewe->setModel(e.Read());
    ui->tableViewr->setModel(R.Read());

    refresh();


   int ret=A.connect_arduino(); // launch the connection to arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
        QTimer *timer1=new QTimer(this);
         connect(timer1 ,SIGNAL(timeout()),this,SLOT(showTime()));
         timer1->start();

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::get_volunteer_info);
        timer->start(1000); // Start the timer with a 1000ms interval

/*
   QTimer *timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(runLoop()));
         timer->start(1000);*/

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

    //maps
  /* QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
*/
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
//Nour


void MainWindow::on_pushButton_createe_clicked()
{
   // Get information entered in the 7 fields
  int id_event=ui->lineEdit_id_3->text().toInt();
   QString ename=ui->lineEdit_Name->text();
    QString place=ui->lineEdit_place->text();
    QString etype=ui->lineEdit_type_2->text();
    QString goals =ui->lineEdit_goals->text();
    QDate edate =ui->lineEdit_edate->date();
     int enbguests=ui->lineEdit_nb_2->text().toInt();
      int id_employee=ui->lineEdit_idemp->text().toInt();


   class event e(id_event, ename, place, etype, goals, edate, enbguests, id_employee);
                             // using information entered in the interface

   bool test=e.Create(); // insert the object into the databse Student table
                         // and et the returned value of query.exec()

   if(test) // if the query is executed  ==> QMessageBox::information
   {
       // Refresh
       ui->tableViewe->setModel(e.Read());

       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("insert done \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       cleart_form();

   }
   else // if the query is not executed  ==> QMessageBox::critical
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("insert failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
cleart_form();
}

void MainWindow::on_pushButton_deletee_clicked()
{
    int id_event =ui->lineEdit_IDS_5->text().toInt();
    bool test=e.Delete(id_event);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableViewe->setModel(e.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_IDS_5->clear();
}
void MainWindow::on_pushButton_updatee_clicked()
{
    // Get information entered in the 3 fields
    int id_event=ui->lineEdit_id_3->text().toInt();
     QString ename=ui->lineEdit_Name->text();
      QString place=ui->lineEdit_place->text();
      QString etype=ui->lineEdit_type_2->text();
      QString goals =ui->lineEdit_goals->text();
      QDate edate =ui->lineEdit_edate->date();
       int enbguests=ui->lineEdit_nb_2->text().toInt();
        int id_employee=ui->lineEdit_idemp->text().toInt();


        class event e(id_event, ename, place, etype, goals,edate, enbguests, id_employee);

                    bool test =e.update();
                    if(test )
                    {
                        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("update successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
  ui-> tableViewe->setModel(e.Read());
cleart_form();
                    }
                    else{
                        QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("update failed.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    cleart_form();}

}
void MainWindow::on_camera_clicked()
{
    c= new Camera();
    c->show();
}


//sort
void MainWindow::on_comboBox_sorte_activated()
{
    if(ui->comboBox_sorte->currentText()=="Place")
           {
               ui->tableViewe->setModel(e.sortPlace());

           }else if(ui->comboBox_sorte->currentText()=="Name")
           {
               ui->tableViewe->setModel(e.sortName());

           }else
           {
               ui->tableViewe->setModel(e.sortNbguests());
           }
}

//search

void MainWindow::on_lineEdit_recherchee_cursorPositionChanged()
{
    QString rech=ui->lineEdit_recherchee->text();
        ui->tableViewe->setModel(e.recherche(rech));

}
//PDF

void MainWindow::on_pushButton_PDFe_clicked()
{
    QPdfWriter pdf("C:\\Users\\rhy16\\OneDrive\\Desktop\\Integration\\PDF_event.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"List of Event");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(300,3300,"Id Event");
                 painter.drawText(1300,3300,"Name");
                 painter.drawText(2300,3300,"Place");
                 painter.drawText(3300,3300,"Type");
                 painter.drawText(4300,3300,"Goals");
                 painter.drawText(5300,3300,"Date");
                 painter.drawText(7300,3300,"Nb guests");
                 painter.drawText(8300,3300,"Id Employee");
                 painter.drawRect(100,3000,9400,10700);

                 QSqlQuery query;
                 query.prepare("SELECT * FROM event");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1300,i,query.value(1).toString());
                     painter.drawText(2300,i,query.value(2).toString());
                     painter.drawText(3300,i,query.value(3).toString());
                     painter.drawText(4300,i,query.value(4).toString());
                     painter.drawText(5300,i,query.value(5).toString());
                     painter.drawText(7300,i,query.value(6).toString());
                     painter.drawText(8300,i,query.value(7).toString());
                    i = i + 350;
                 }
                 QMessageBox::information(this, QObject::tr("PDF Downloaded !"),
                 QObject::tr("PDF Downloaded ! \n" "Click Cancel to exit."), QMessageBox::Cancel);
}


//stat
void MainWindow::on_pushButton_statcharte_clicked()
{

    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM event WHERE etype='online'");
       query.exec();
       query.next();
       int onlineCount = query.value(0).toInt();

       query.prepare("SELECT COUNT(*) FROM event WHERE etype = 'presentiel'");
       query.exec();
       query.next();
       int presentielCount = query.value(0).toInt();

       QPieSeries *series = new QPieSeries();
       series->append("online", onlineCount);
       series->append("presentiel", presentielCount);

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("event Type");

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       QDialog *dialog = new QDialog(this);
       dialog->setWindowTitle("event Type");
       dialog->resize(400, 300);
       QVBoxLayout *layout = new QVBoxLayout(dialog);
       layout->addWidget(chartView);

       dialog->exec();


}
void MainWindow::on_pushButton_stattexte_clicked()
{
    // Query the database to get the number of active and pending collaborators
          QSqlQuery query;
          query.prepare("SELECT COUNT(*) FROM event WHERE etype='online'");
          query.exec();
          query.next();
          int onlineCount = query.value(0).toInt();

          query.prepare("SELECT COUNT(*) FROM event WHERE etype = 'presentiel'");
          query.exec();
          query.next();
          int presentielCount = query.value(0).toInt();

          // Calculate the percentage of active and pending collaborators
          int totalCount = onlineCount + presentielCount;
          double onlinePercentage = static_cast<double>(onlineCount) / totalCount * 100;
          double presentielPercentage = static_cast<double>(presentielCount) / totalCount * 100;

          // Display the result to the user
          QString result = QString("online: %1%  presentiel: %2%").arg(onlinePercentage).arg(presentielPercentage);
          QMessageBox::information(this, "event Type", result);
}
bool MainWindow::get_volunteer_info()
{QString ID_PATIENT=A.read_from_arduino();

    QSqlQuery query;

    query.prepare("SELECT FIRST_NAME FROM PATIENT WHERE ID_PATIENT = :ID_PATIENT");
    query.bindValue(":ID_PATIENT", ID_PATIENT);

    if(query.exec() && query.next()) {
        QString FIRST_NAME = query.value(0).toString();



        // Display the retrieved client info on the LCD screen
        QString message = "Hello " + FIRST_NAME;
        qDebug()<<message;
        A.write_to_arduino(message.toUtf8());
        qDebug()<<"sent!";
    } else {
        qDebug() << "Error executing SQL query: " << query.last(); }
    return 0;
}

//MINOUU
void MainWindow::on_pushButton_add_clicked()
{
    // Get information entered in the interface
    int ID_EMPLOYEE = ui->lineEdit_ID_EMPLOYEE_2->text().toInt();
    QString EFIRST_NAME= ui->lineEdit_EFIRST_NAME->text();
    QString ELAST_NAME = ui->lineEdit_ELAST_NAME->text();
    QString EGENDER = ui->lineEdit_EGENDER->text();
    QString ROLES = ui->lineEdit_ROLES->text();
    QDate EDOB = ui->dateEdit_EDOB->date();
    QString DIPLOMAS = ui->lineEdit_DIPLOMAS->text();
    QString EPASSWORD = ui->lineEdit_EPASSWORD->text();
    QString IDCARD = ui->lineEdit_IDCARD->text();

    // Create an Employee object using the entered information
    Employee E(ID_EMPLOYEE, EFIRST_NAME, ELAST_NAME, EGENDER, ROLES, EDOB, DIPLOMAS, EPASSWORD, IDCARD);

    // Insert the object into the database Employee table
    bool query_result = E.Create();

    if(query_result) // if the query is executed  ==> QMessageBox::information
    {
        // Refresh the table view with updated data
         ui->tableView->setModel(E.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Insert successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else // if the query is not executed  ==> QMessageBox::critical
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Insert failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    cleart_form();
}

void MainWindow::on_pushButton_delete_clicked() //delete
{
    int ID_EMPLOYEE = ui->lineEdit_ID_EMPLOYEE->text().toInt();
    bool deleted = E.Delete(ID_EMPLOYEE);

    if (deleted)
    {
        // Refresh the table view
        ui->tableView->setModel(E.Read());

        QMessageBox::information(nullptr, QObject::tr("Success"),
                                 QObject::tr("Employee deleted.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Failed to delete employee.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->lineEdit_ID_EMPLOYEE->clear();
}

void MainWindow::on_pushButton_update_clicked()
{
    int ID_EMPLOYEE = ui->lineEdit_ID_EMPLOYEE_2->text().toInt();
    QString EFIRST_NAME= ui->lineEdit_EFIRST_NAME->text();
    QString ELAST_NAME = ui->lineEdit_ELAST_NAME->text();
    QString EGENDER = ui->lineEdit_EGENDER->text();
    QString ROLES = ui->lineEdit_ROLES->text();
    QDate EDOB = ui->dateEdit_EDOB->date();
    QString DIPLOMAS = ui->lineEdit_DIPLOMAS->text();
    QString EPASSWORD = ui->lineEdit_EPASSWORD->text();
    QString IDCARD = ui->lineEdit_IDCARD->text();



        Employee E(ID_EMPLOYEE, EFIRST_NAME, ELAST_NAME, EGENDER, ROLES, EDOB, DIPLOMAS , EPASSWORD , IDCARD);

                       bool test =E.Update();
                       if(test )
                       {
                           QMessageBox::information(nullptr, QObject::tr("database is open"),
                                       QObject::tr("update successful.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
     ui-> tableView->setModel(E.Read());
cleart_form();

                       }
                       else{
                           QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                       QObject::tr("update failed.\n"

                                         "Click Cancel to exit."), QMessageBox::Cancel);}
                       cleart_form();
   }

void MainWindow::on_comboBox_sort_activated()
{
    // Check which option is selected in the combo box
    if(ui->comboBox_sort->currentText()=="Role")
           {
         // If "Role" is selected, sort the employee data by role and display it in the table view
               ui->tableView->setModel(E.sortrole());

           }else if(ui->comboBox_sort->currentText()=="Diploma")
           {
         // If "Diploma" is selected, sort the employee data by diploma and display it in the table view
               ui->tableView->setModel(E.sortdiploma());

           }else
           {
         // If neither "Role" nor "Diploma" is selected, sort the employee data by gender and display it in the table view
               ui->tableView->setModel(E.sortgender());
           }
}

void MainWindow::on_lineEdit_recherche_cursorPositionChanged()
{
    // Get the text entered by the user in the search bar
    QString rech=ui->lineEdit_recherche->text();
    // Search for the entered text in the employee data and display the results in the table view
        ui->tableView->setModel(E.recherche(rech));

}

void MainWindow::on_pushButton_PDF_clicked()
{
    // Create a PDF file and specify the file path

    QPdfWriter pdf("C:\\Users\\rhy16\\OneDrive\\Desktop\\Integration\\PDF_employee.pdf");
    // Create a painter to draw on the PDF

          QPainter painter(&pdf);
          // Set the font and color for the painter

          int i = 4000;
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Time New Roman", 25));

                 // Add the title "List of Employees" to the PDF

                 painter.drawText(3000,1400,"List of Employees");

                 // Set the font and color for the painter again
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));

                 // Add a rectangle to the PDF to separate the header from the employee data
                 painter.drawRect(100,3000,9400,500);

                 // Add labels for each column in the employee data table
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(300,3300,"Id Employee");
                 painter.drawText(1300,3300,"First Name");
                 painter.drawText(2300,3300,"Last Name");
                 painter.drawText(3500,3300,"Gender");
                 painter.drawText(4600,3300,"Role");
                 painter.drawText(6000,3300,"Date of birth");
                 painter.drawText(8000,3300,"Diplomas");

                 // Add another rectangle to the PDF to hold the employee data
                 painter.drawRect(100,3000,9400,10700);

                 // Connect to the database and select all the employee data
                 QSqlQuery query;
                 query.prepare("SELECT * FROM Employee");
                 query.exec();

                 // Loop through all the employee data and add it to the PDF
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1300,i,query.value(1).toString());
                     painter.drawText(2300,i,query.value(2).toString());
                     painter.drawText(3500,i,query.value(3).toString());
                     painter.drawText(4700,i,query.value(4).toString());
                     painter.drawText(6000,i,query.value(5).toString());
                     painter.drawText(8100,i,query.value(6).toString());

                    // Increase the vertical position for the next employee data row
                    i = i + 350;
                 }

                 // Show a message box to confirm that the PDF has been downloaded
                 QMessageBox::information(this, QObject::tr("PDF Downloaded !"),
                 QObject::tr("PDF Downloaded ! \n" "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pushButton_7_clicked() //stat
{

           // Query the database to get the number of therapits , assistants and doctors
           QSqlQuery query;
           query.prepare("SELECT COUNT(*) FROM Employee WHERE ROLES = 'Assistant'");
           query.exec();
           query.next();
           int AssistantCount = query.value(0).toInt();

           query.prepare("SELECT COUNT(*) FROM Employee WHERE  ROLES = 'Therapist'");
           query.exec();
           query.next();
           int TherapistCount = query.value(0).toInt();

           query.prepare("SELECT COUNT(*) FROM Employee WHERE  ROLES = 'Doctor'");
           query.exec();
           query.next();
           int DoctorCount = query.value(0).toInt();


           // Create a pie series and add the data to it
           QPieSeries *series = new QPieSeries();
           series->append("Assistant", AssistantCount);
           series->append("Therapist",TherapistCount );
           series->append("Doctor", DoctorCount);

           // Create a chart and add the series to it
           QChart *chart = new QChart();
           chart->addSeries(series);
           chart->setTitle("Employee ROLES");

           // Create a chart view and set the chart as its model
           QChartView *chartView = new QChartView(chart);
           chartView->setRenderHint(QPainter::Antialiasing);

           // Create a dialog to display the chart view
           QDialog *dialog = new QDialog(this);
           dialog->setWindowTitle("Employee ROLES");
           dialog->resize(400, 300);
           QVBoxLayout *layout = new QVBoxLayout(dialog);
           layout->addWidget(chartView);

           // Show the dialog
           dialog->exec();
}

void MainWindow::on_pushButton_5_clicked() // authentication
{
    Authentication *authentication = new Authentication();
        authentication->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    widget w;
    w.exec();
}

void MainWindow::on_pushButton_add_2_clicked()
{/*
    QString value = A.read_from_arduino2(); // assuming A is an instance of your Arduino object
       ui->lineEdit_IDCARD->setText(value);

           // Execute the query to check if the value is present in the database
           QSqlQuery query;
           query.prepare("SELECT IDCARD FROM EMPLOYEE WHERE IDCARD = :IDCARD");
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
           }*/
}
/*
void MainWindow::update_label()
{
    QString data = A.read_from_arduino();

    if(data == "1")
        ui->lineEdit_IDCARD->setText("ON");
   else if (data == "0")
      ui->lineEdit_IDCARD->setText("OFF");
}*/


//DONIA

void MainWindow::showTime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->Digital_clock->setText(time_text);
}


void MainWindow::on_pushButton_create_clicked()
{
   // Get information entered in the 7 fields
  int id_patient=ui->lineEdit_id->text().toInt();
   QString first_name=ui->lineEdit_Fname->text();
    QString last_name=ui->lineEdit_Lname->text();
    QDate dob=ui->lineEdit_dob->date();
    QString gender =ui->lineEdit_gender->text();
    QString email =ui->lineEdit_email->text();
     QString address=ui->lineEdit_ad->text();
      QString typeofdiag=ui->lineEdit_type->text();
      int pnumber=ui->lineEdit_nb->text().toInt();


   class patient p(id_patient, first_name, last_name, dob,gender,email,address,typeofdiag,pnumber);
                             // using information entered in the interface

   bool test=p.Create(); // insert the object into the databse Student table
                         // and et the returned value of query.exec()

   if(test) // if the query is executed  ==> QMessageBox::information
   {
       // Refresh
       ui->tableViewp->setModel(p.Read());

       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("insert done \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       cleart_form();

   }
   else // if the query is not executed  ==> QMessageBox::critical
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("insert failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   cleart_form();

}

void MainWindow::on_pushButton_deletep_clicked()
{
    int id_patient =ui->lineEdit_IDS->text().toInt();
    bool test=p.Delete(id_patient);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableViewp->setModel(p.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_IDS->clear();
}
void MainWindow::on_pushButton_updatep_clicked()
{
    // Get information entered in the 3 fields
    int id_patient=ui->lineEdit_id->text().toInt();
     QString first_name=ui->lineEdit_Fname->text();
      QString last_name=ui->lineEdit_Lname->text();
      QDate dob=ui->lineEdit_dob->date();
      QString gender =ui->lineEdit_gender->text();
      QString email =ui->lineEdit_email->text();
       QString address=ui->lineEdit_ad->text();
        QString typeofdiag=ui->lineEdit_type->text();
        int pnumber=ui->lineEdit_nb->text().toInt();



        class patient p(id_patient, first_name, last_name, dob,gender,email,address,typeofdiag,pnumber);

                    bool test =p.update();
                    if(test)
                    {
                        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("update successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
  ui-> tableViewp->setModel(p.display());
  cleart_form();

                    }
                    else{
                        QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("update failed.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);}
                    cleart_form();

}


void MainWindow::on_comboBox_sortp_activated()
{
    if(ui->comboBox_sortp->currentText()=="First_Name")
           {
               ui->tableViewp->setModel(p.sortName());

           }else if(ui->comboBox_sortp->currentText()=="Gender")
           {
               ui->tableViewp->setModel(p.sortgender());

           }else
           {
               ui->tableViewp->setModel(p.sorttype());
           }
}


void MainWindow::on_lineEdit_recherchep_cursorPositionChanged()
{
    QString rech=ui->lineEdit_recherchep->text();
    ui->tableViewp->setModel(p.recherchep(rech));

}

void MainWindow::on_pushButton_PDFp_clicked()
{
    QPdfWriter pdf("C:\\Users\\rhy16\\OneDrive\\Desktop\\Integration\\PDF_patient.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"List of Patients");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(300,3300,"Id Patient");
                 painter.drawText(1300,3300,"FName");
                 painter.drawText(2300,3300,"LName");
                 painter.drawText(3300,3300,"DOB");
                 painter.drawText(4300,3300,"Gender");
                 painter.drawText(5300,3300,"Email");
                 painter.drawText(7300,3300,"Address");
                 painter.drawText(8300,3300,"Type Of Diag");
                 painter.drawText(7300,3300,"PNumber");
                 painter.drawRect(100,3000,9400,10700);

                 QSqlQuery query;
                 query.prepare("SELECT * FROM patient");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1300,i,query.value(1).toString());
                     painter.drawText(2300,i,query.value(2).toString());
                     painter.drawText(3300,i,query.value(3).toString());
                     painter.drawText(4300,i,query.value(4).toString());
                     painter.drawText(5300,i,query.value(5).toString());
                     painter.drawText(7300,i,query.value(6).toString());
                     painter.drawText(8300,i,query.value(7).toString());
                    i = i + 350;
                 }
                 QMessageBox::information(this, QObject::tr("PDF Downloaded !"),
                 QObject::tr("PDF Downloaded ! \n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_statchartp_clicked()
{

    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM patient WHERE gender='Female'");
       query.exec();
       query.next();
       int femaleCount = query.value(0).toInt();

       query.prepare("SELECT COUNT(*) FROM patient WHERE gender = 'Male'");
       query.exec();
       query.next();
       int maleCount = query.value(0).toInt();

       QPieSeries *series = new QPieSeries();
       series->append("Female", femaleCount);
       series->append("Male", maleCount);

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Patient Gender");

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       QDialog *dialog = new QDialog(this);
       dialog->setWindowTitle("Patient Gender");
       dialog->resize(400, 300);
       QVBoxLayout *layout = new QVBoxLayout(dialog);
       layout->addWidget(chartView);

       dialog->exec();


}
void MainWindow::on_pushButton_stattextp_clicked()
{
    // Query the database to get the number of active and pending collaborators
          QSqlQuery query;
          query.prepare("SELECT COUNT(*) FROM patient WHERE gender='Female'");
          query.exec();
          query.next();
          int femaleCount = query.value(0).toInt();

          query.prepare("SELECT COUNT(*) FROM patient WHERE gender = 'Male'");
          query.exec();
          query.next();
          int maleCount = query.value(0).toInt();

          // Calculate the percentage of active and pending collaborators
          int totalCount = femaleCount + maleCount;
          double femalePercentage = static_cast<double>(femaleCount) / totalCount * 100;
          double malePercentage = static_cast<double>(maleCount) / totalCount * 100;

          // Display the result to the user
          QString result = QString("Male: %1%  Female: %2%").arg(malePercentage).arg(femalePercentage);
          QMessageBox::information(this, "Patient Gender", result);
}




void MainWindow::on_btn_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp"));
    if (QString::compare(filename, QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if (valid)
        {
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //error handling
        }
    }
}

void MainWindow::updatep_label()
{
   /* QString data = A.read_from_arduino();

    if(data == "1")
        ui->label_12->setText("ON");
   else if (data == "0")
      ui->label_12->setText("OFF");*/
}


int MainWindow::control_idpp(int id_patient)
{
  /*  QSqlQuery query;
    query.prepare("SELECT ID_PATIENT FROM Patient WHERE ID_PATIENT = :id_patient");
    query.bindValue(":id_patient", id_patient);
    if (query.exec() && query.next()) {
           // ID patient exists in the database, return the ID patient
           int idp = query.value(0).toInt();
           return idp;
       } else {
           // ID patient does not exist in the database, return 0
           return 0;
}*/
}

int MainWindow::control_type(QString type)
{
  /*  QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Patient WHERE TYPEOFDIAG = :type");
    query.bindValue(":type", type);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0 && type == "critical") {
            // TYPEOFDIAG is critical and at least one patient exists, return 1
            return 1;
        } else  {
            // TYPEOFDIAG is not critical or no patients with the given type exist, return 0
            return 0;
        }
    } else {
        // Query failed, return -1 or throw an exception as appropriate
        return -1;
    }*/
}

void MainWindow::on_pushButton_arduinop_clicked()
{
    /*
    int ID_PATIENT = ui->lineEdit_id_2->text().toInt();
    int br = control_idp(ID_PATIENT);
    if (br != 0) {
        bool ok;
        QString type = QInputDialog::getText(this, tr("Enter the Type"),
                                             tr("Type:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !type.isEmpty()) {
            int type_val = control_type(type);
            QByteArray byteArray;
            if (type_val == 1) {
                byteArray = QByteArray::number(br);
            } else {
                byteArray = "-1";
            }
            A.write_to_arduino(byteArray);
            qDebug() << byteArray;
        } else {
            QMessageBox::information(nullptr, QObject::tr("Error"),
                                     QObject::tr("Invalid Type.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        A.write_to_arduino("0");
        QMessageBox::information(nullptr, QObject::tr("Error"),
                    QObject::tr("Patient not found.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);
    }*/
}

//Meriem

void MainWindow::cleart_form()
{
    ui->lineEdit_ID_TREATMENT->clear();
    ui->lineEdit_TNAME->clear();
    ui->lineEdit_STARTDATE->clear();
    ui->lineEdit_ENDDATE->clear();
    ui->lineEdit_TYPEE->clear();
    ui->lineEdit_DOSAGE->clear();
    ui->lineEdit_TCOST->clear();
    ui->lineEdit_ID->clear();

    ui->lineEdit_id_3->clear();
    ui->lineEdit_Name->clear();
   ui->lineEdit_place->clear();
      ui->lineEdit_type_2->clear();
      ui->lineEdit_goals->clear();
      ui->lineEdit_edate->clear();
       ui->lineEdit_nb_2->clear();
        ui->lineEdit_idemp->clear();

        ui->lineEdit_id->clear();
        ui->lineEdit_Fname->clear();
        ui->lineEdit_Lname->clear();
       ui->lineEdit_dob->clear();
        ui->lineEdit_gender->clear();
         ui->lineEdit_email->clear();
          ui->lineEdit_ad->clear();
           ui->lineEdit_type->clear();
            ui->lineEdit_nb->clear();

            ui->res->clear();
            ui->TITLE->clear();
           ui->RLANGUAGE->clear();
            ui->RTYPE->clear();
            ui->RAVAILIBILITY->clear();
            ui->RDATE->clear();
           ui->RDESCRIPTION->clear();
            ui->ID_EMPLOYEE->clear();

            ui->lineEdit_ID_EMPLOYEE_2->clear();
            ui->lineEdit_EFIRST_NAME->clear();
           ui->lineEdit_ELAST_NAME->clear();
            ui->lineEdit_EGENDER->clear();
           ui->lineEdit_ROLES->clear();
            ui->dateEdit_EDOB->clear();
             ui->lineEdit_DIPLOMAS->clear();
             ui->lineEdit_EPASSWORD->clear();
           ui->lineEdit_IDCARD->clear();
}


void MainWindow::on_pushButton_Add_clicked()
{
   // Get information entered in the 8 fields
   int ID_TREATMENT=ui->lineEdit_ID_TREATMENT->text().toInt();
   QString TNAME = ui->lineEdit_TNAME->text();
   QDate START_DATE = ui->lineEdit_STARTDATE->date();
   QDate END_DATE = ui->lineEdit_ENDDATE->date();
   QString TYPEE = ui->lineEdit_TYPEE->text();
   QString DOSAGE = ui->lineEdit_DOSAGE->text();
   int TCOST = ui->lineEdit_TCOST->text().toInt();
   int ID_EMPLOYEE=ui->lineEdit_ID->text().toInt();

   Treatment T(ID_TREATMENT, TNAME, START_DATE, END_DATE, TYPEE, DOSAGE, TCOST, ID_EMPLOYEE);


   // object instantiation


                              // using information entered in the interface

   bool test=T.Create(); // insert the object into the databse Treatment table
                         // and et the returned value of query.exec()

   if(test) // if the query is executed  ==> QMessageBox::information
   {
       // Refresh
       ui->tableViewt->setModel(T.Read());

       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("insert done \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else // if the query is not executed  ==> QMessageBox::critical
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("insert failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   cleart_form();

}

void MainWindow::on_pushButton_Delete_clicked()
{
    int ID_TREATMENT =ui->lineEdit_IDS_2->text().toInt();
    bool test=T.Delete(ID_TREATMENT);
    if(test)
    {


        // Refresh (Actualiser)
        ui->tableViewt->setModel(T.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
     ui->lineEdit_IDS_2->clear();

}
void MainWindow::on_pushButton_updatet_clicked()
{
    // Get information entered in the 3 fields
    int ID_TREATMENT=ui->lineEdit_ID_TREATMENT->text().toInt();
    QString TNAME = ui->lineEdit_TNAME->text();
    QDate START_DATE = ui->lineEdit_STARTDATE->date();
    QDate END_DATE = ui->lineEdit_ENDDATE->date();
    QString TYPEE = ui->lineEdit_TYPEE->text();
    QString DOSAGE = ui->lineEdit_DOSAGE->text();
    int TCOST = ui->lineEdit_TCOST->text().toInt();
    int ID_EMPLOYEE=ui->lineEdit_ID->text().toInt();


      Treatment T(ID_TREATMENT, TNAME, START_DATE, END_DATE, TYPEE, DOSAGE, TCOST, ID_EMPLOYEE);

                    bool test =T.update();
                    if(test )
                    {
                        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("update successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
                        cleart_form();
  ui-> tableViewt->setModel(T.Read());


                    }
                    else{
                        QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("update failed.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);}
                   cleart_form();
}

void MainWindow::on_comboBox_sortt_activated()
{
    if(ui->comboBox_sortt->currentText()=="Cost")
           {
               ui->tableViewt->setModel(T.sortcost());

           }else if(ui->comboBox_sortt->currentText()=="Type")
           {
               ui->tableViewt->setModel(T.sorttype());

           }else
           {
               ui->tableViewt->setModel(T.sortdosage());
           }
}

void MainWindow::on_lineEdit_recherchet_cursorPositionChanged()
{
    QString recht=ui->lineEdit_recherchet->text();
        ui->tableViewt->setModel(T.recherchet(recht));

}

void MainWindow::on_pushButton_PDFt_clicked()
{
    QPdfWriter pdf("C:\\Users\\rhy16\\OneDrive\\Desktop\\Integration\\PDF_treatment.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"List of Treatments");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(300,3300,"Id Treatment");
                 painter.drawText(1300,3300,"Name");
                 painter.drawText(2200,3300,"Start Date");
                 painter.drawText(4000,3300,"End Date");
                 painter.drawText(5800,3300,"Type");
                 painter.drawText(7000,3300,"Dosage");
                 painter.drawText(8000,3300,"Cost");
                 painter.drawText(8500,3300,"Id Employee");
                 painter.drawRect(100,3000,9400,10700);

                 QSqlQuery query;
                 query.prepare("SELECT * FROM Treatment");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1300,i,query.value(1).toString());
                     painter.drawText(2200,i,query.value(2).toString());
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

void MainWindow::on_pushButton_QRcode_clicked()
{
    QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("select * from Treatment");
    QString text ="https://www.talkwithfrida.com/learn/65-tips-and-tricks-to-better-manage-adult-adhd-without-meds/";


                       //text="user data";
                       using namespace qrcodegen;
                         // Create the QR Code object
                         QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                         qint32 sz = qr.getSize();
                         QImage im(sz,sz, QImage::Format_RGB32);
                           QRgb black = qRgb(  0,  0,  0);
                           QRgb white = qRgb(255,255,255);
                         for (int y = 0; y < sz; y++)
                           for (int x = 0; x < sz; x++)
                             im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                         ui->qr_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

}

void MainWindow::on_pushButton_statchartt_clicked()
{

    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM Treatment WHERE TYPEE='Therapy'");
       query.exec();
       query.next();
       int therapyCount = query.value(0).toInt();

       query.prepare("SELECT COUNT(*) FROM Treatment WHERE TYPEE = 'Medication'");
       query.exec();
       query.next();
       int medicationCount = query.value(0).toInt();

       QPieSeries *series = new QPieSeries();
       series->append("Therapy", therapyCount);
       series->append("Medication", medicationCount);

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Treatment Type");

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       QDialog *dialog = new QDialog(this);
       dialog->setWindowTitle("Treatment Type");
       dialog->resize(400, 300);
       QVBoxLayout *layout = new QVBoxLayout(dialog);
       layout->addWidget(chartView);

       dialog->exec();


}
void MainWindow::on_pushButton_stattextt_clicked()
{
    // Query the database to get the number of active and pending collaborators
          QSqlQuery query;
          query.prepare("SELECT COUNT(*) FROM Treatment WHERE TYPEE='Therapy'");
          query.exec();
          query.next();
          int therapyCount = query.value(0).toInt();

          query.prepare("SELECT COUNT(*) FROM Treatment WHERE TYPEE = 'Medication'");
          query.exec();
          query.next();
          int medicationCount = query.value(0).toInt();

          // Calculate the percentage of active and pending collaborators
          int totalCount = therapyCount + medicationCount;
          double therapyPercentage = static_cast<double>(therapyCount) / totalCount * 100;
          double medicationPercentage = static_cast<double>(medicationCount) / totalCount * 100;

          // Display the result to the user
          QString result = QString("Therapy: %1%  Medication: %2%").arg(therapyPercentage).arg(medicationPercentage);
          QMessageBox::information(this, "Treatment Type", result);
}

void MainWindow::on_pushButton_sms_clicked() {

      sendSMS( "Smart ADHD center","21627230407","e447e3cf","7lStGudOJFtxzMFH","Don't forget your medecine !");

}

void MainWindow::sendSMS(QString fromNumber, QString toNumber, QString apiKey, QString apiSecret, QString message)

   {


   QNetworkAccessManager manager(this);

         QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
         connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onSMSResponse);

         QString url = QString("https://rest.nexmo.com/sms/json?api_key=%1&api_secret=%2&from=%3&to=%4&text=%5")
                 .arg(apiKey).arg(apiSecret).arg(fromNumber).arg(toNumber).arg(message);

         QNetworkRequest request(url);
         QSslConfiguration sslConfig = request.sslConfiguration();
         sslConfig.setProtocol(QSsl::TlsV1_2);
         request.setSslConfiguration(sslConfig);
         networkManager->get(request);
 }
 void MainWindow::onSMSResponse(QNetworkReply *reply)
 {
     QString response = reply->readAll();
     qDebug() << "SMS response: " << response;
     // Handle the response as needed
 }


void MainWindow::on_pushButton_whatsapp_clicked()
{

    QDesktopServices::openUrl(QUrl("https://wa.me/+21658412360", QUrl::TolerantMode));

}

void MainWindow::updatet_label()
{
   /* QString data = A.read_from_arduino();

    if(data == "1")
        ui->label_12->setText("ON");
   else if (data == "0")
      ui->label_12->setText("OFF");*/
}




//Jawher

void MainWindow::cleara_form()
{
  ui->lineEdit_ID_APPOINTMENT->clear();
    ui->lineEdit_ADATE->clear();
     ui->lineEdit_ATYPE->clear();
    ui->lineEdit_ADESCRIPTION->clear();
    ui->lineEdit_APLACE->clear();
    ui->lineEdit_ID_PATIENT_2->clear();
    ui->lineEdit_ID_2->clear();
}

void MainWindow::on_pushButton_Adda_clicked()
{
   // Get information entered in the 3 fields
   int ID_APPOINTMENT=ui->lineEdit_ID_APPOINTMENT->text().toInt();
   QDate ADATE = ui->lineEdit_ADATE->date();
   QString ATYPE = ui->lineEdit_ATYPE->text();
   QString ADESCRIPTION = ui->lineEdit_ADESCRIPTION->text();
   QString APLACE = ui->lineEdit_APLACE->text();
   int ID_PATIENT=ui->lineEdit_ID_PATIENT_2->text().toInt();
   int ID_EMPLOYEE=ui->lineEdit_ID_2->text().toInt();
   Appointment Ap(ID_APPOINTMENT, APLACE, ADESCRIPTION, ATYPE, ADATE,ID_PATIENT, ID_EMPLOYEE );




                              // using information entered in the interface

   bool test=Ap.Create(); // insert the object into the databse Appointment table
                         // and et the returned value of query.exec()

   if(test) // if the query is executed  ==> QMessageBox::information
   {
       // Refresh
       ui->tableViewa->setModel(Ap.Read());
       refresh();

       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("insert done \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

   }
   else // if the query is not executed  ==> QMessageBox::critical
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("insert failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
cleara_form();
}

void MainWindow::on_pushButton_Deletea_clicked()
{
    int ID_APPOINTMENT =ui->lineEdit_IDS_3->text().toInt();
    bool test=Ap.Delete(ID_APPOINTMENT);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableViewa->setModel(Ap.Read());
        refresh();

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_IDS_3->clear();
}
void MainWindow::on_pushButton_updatea_clicked()
{
    int ID_APPOINTMENT=ui->lineEdit_ID_APPOINTMENT->text().toInt();
    QString APLACE=ui->lineEdit_APLACE->text();
    QString ADESCRIPTION=ui->lineEdit_ADESCRIPTION->text();
    QString ATYPE=ui->lineEdit_ATYPE->text();
    QDate ADATE=ui->lineEdit_ADATE->date();
    int ID_EMPLOYEE=ui->lineEdit_ID_2->text().toInt();
    int ID_PATIENT=ui->lineEdit_ID_PATIENT_2->text().toInt();

    Appointment Ap(ID_APPOINTMENT, APLACE, ADESCRIPTION, ATYPE, ADATE,ID_PATIENT, ID_EMPLOYEE );

    bool test =Ap.update();
     if(test )
     {
         QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("update successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
         ui-> tableViewa->setModel(Ap.display());
         refresh();
         cleara_form();
     }
     else{
         QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("update failed.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);
     }
     cleara_form();
                    }


void MainWindow::on_pushButton_excel_clicked()
{
    //exportation
      QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation of the folder Excel "), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
      if (fileName.isEmpty())
      return;

      EXCEL obj(fileName, "app", ui->tableViewa);

                // you can change the column order and
                // choose which colum to export
        obj.addField(0, "ID_APPOINTMENT", "number");
        obj.addField(1, "APLACE", "char(20)");
        obj.addField(2, "ADESCRIPTION", "char(20)");
        obj.addField(3, "ATYPE", "char(20)");
        obj.addField(4, "ADATE", "char(20)");
        obj.addField(5, "ID_EMPLOYEE", "number");
        obj.addField(6, "ID_PATIENT", "number");



        int retVal = obj.export2Excel();

                       if( retVal > 0)
                       {
                           QMessageBox::information(this, tr("Done!"),
                                                    QString(tr("%1 The elements are exported!")).arg(retVal)
                                                    );
                       }
}

void MainWindow::on_lineEdit_recherchea_cursorPositionChanged()
{
    QString rech=ui->lineEdit_recherchea->text();
    ui->tableViewa->setModel(Ap.recherche(rech));

}

void MainWindow::on_comboBox_sorta_activated()
{
    if(ui->comboBox_sorta->currentText()=="Date")
           {
               ui->tableViewa->setModel(Ap.sortADATE());

           }else if(ui->comboBox_sorta->currentText()=="Place")
           {
               ui->tableViewa->setModel(Ap.sortAPLACE());

           }else
           {
               ui->tableViewa->setModel(Ap.sortATYPE());
           }
}

void MainWindow::on_pushButton_PDFa_clicked()
{
    QPdfWriter pdf("C:\\Users\\rhy16\\OneDrive\\Desktop\\Integration\\PDF_appointment.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::blue);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"List of Appointments");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(300,3300,"Id Appointment");
                 painter.drawText(1500,3300,"Date");
                 painter.drawText(3500,3300,"Place");
                 painter.drawText(4800,3300,"Description");
                 painter.drawText(6000,3300,"Type");
                 painter.drawText(7000,3300,"Id Employee");
                 painter.drawText(8500,3300,"Id Patient");
                 painter.drawRect(100,3000,9400,10700);

                 QSqlQuery query;
                 query.prepare("SELECT * FROM Appointment");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(300,i,query.value(0).toString());
                     painter.drawText(1500,i,query.value(1).toString());
                     painter.drawText(3500,i,query.value(2).toString());
                     painter.drawText(4800,i,query.value(3).toString());
                     painter.drawText(6000,i,query.value(4).toString());
                     painter.drawText(7500,i,query.value(5).toString());
                     painter.drawText(8700,i,query.value(6).toString());
                    i = i + 350;
                 }
                 QMessageBox::information(this, QObject::tr("PDF Downloaded !"),
                 QObject::tr("PDF Downloaded ! \n" "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::refresh() {
    // Clear any previously set date formats
    ui->CalendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

    // Get the dates of all the appointments from the database
    QSqlQuery query("SELECT ADATE FROM Appointment");
    QList<QDate> appointmentDates;
    while (query.next()) {
        QString dateString = query.value(0).toString();
        QRegularExpression regex("(\\d{4})-(\\d{2})-(\\d{2})");
        QRegularExpressionMatch match = regex.match(dateString);
        if (!match.hasMatch()) {
            qDebug() << "Failed to parse date: " << dateString;
            continue; // skip to the next iteration of the loop
        }
        int year = match.captured(1).toInt();
        int month = match.captured(2).toInt();
        int day = match.captured(3).toInt();
        QDate date(year, month, day);
        if (!date.isValid()) {
            qDebug() << "Invalid date: " << dateString;
            continue; // skip to the next iteration of the loop
        }
        appointmentDates.append(date);
    }

    // Create a QTextCharFormat object and set its background color to green
    QTextCharFormat format;
    format.setBackground(Qt::green);
    format.setForeground(Qt::white);

    // Loop through each date in the appointmentDates list and highlight them in green on the QCalendarWidget
    foreach (const QDate &date, appointmentDates) {
        ui->CalendarWidget->setDateTextFormat(date, format);
    }
}

void MainWindow::on_pushButton_statcharta_clicked()
{

    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM Appointment WHERE ATYPE='online'");
       query.exec();
       query.next();
       int onlineCount = query.value(0).toInt();

       query.prepare("SELECT COUNT(*) FROM Appointment WHERE ATYPE = 'presential'");
       query.exec();
       query.next();
       int presentialCount = query.value(0).toInt();

       QPieSeries *series = new QPieSeries();
       series->append("online", onlineCount);
       series->append("presential", presentialCount);

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Appointment Type");

       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);

       QDialog *dialog = new QDialog(this);
       dialog->setWindowTitle("Appointment Type");
       dialog->resize(400, 300);
       QVBoxLayout *layout = new QVBoxLayout(dialog);
       layout->addWidget(chartView);

       dialog->exec();


}
void MainWindow::on_pushButton_stattexta_clicked()
{
    // Query the database to get the number of active and pending collaborators
          QSqlQuery query;
          query.prepare("SELECT COUNT(*) FROM Appointment WHERE ATYPE='online'");
          query.exec();
          query.next();
          int onlineCount = query.value(0).toInt();

          query.prepare("SELECT COUNT(*) FROM Appointment WHERE ATYPE = 'presential'");
          query.exec();
          query.next();
          int presentialCount = query.value(0).toInt();

          // Calculate the percentage of active and pending collaborators
          int totalCount = onlineCount + presentialCount;
          double onlinePercentage = static_cast<double>(onlineCount) / totalCount * 100;
          double presentialPercentage = static_cast<double>(presentialCount) / totalCount * 100;

          // Display the result to the user
          QString result = QString("online: %1%  presential: %2%").arg(onlinePercentage).arg(presentialPercentage);
          QMessageBox::information(this, "Appointment Type", result);
}




//Anas
void MainWindow::on_pushButton_updater_clicked()
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
     ui-> tableViewr->setModel(R.Read());
     cleart_form();


                       }
                       else{
                           QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                       QObject::tr("update failed.\n"

                                         "Click Cancel to exit."), QMessageBox::Cancel);}
                       cleart_form();

   }

void MainWindow::on_pushButton_addr_clicked()//add
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
        ui->tableViewr->setModel(R.Read());
cleart_form();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Insert done \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else // if the query is not executed  ==> QMessageBox::critical
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Insert failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    cleart_form();
}

void MainWindow::on_pushButton_deleter_clicked() //delete
{
    int ID_RESSOURCE =ui->del->text().toInt();//khdina l id li bech nfasskhouha
    bool test=R.Delete(ID_RESSOURCE);

    if(test)
    {
        // Refresh (Actualiser)
        ui->tableViewr->setModel(R.Read());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("delete done\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->del->clear();
}

void MainWindow::on_comboBox_sortr_activated()
{
    if(ui->comboBox_sortr->currentText()=="Language")
           {
               ui->tableViewr->setModel(R.sortlanguage());

           }else if(ui->comboBox_sortr->currentText()=="Availability")
           {
               ui->tableViewr->setModel(R.sortavailability());

           }else
           {
               ui->tableViewr->setModel(R.sorttype());
           }
}

void MainWindow::on_lineEdit_rechercher_cursorPositionChanged()
{
    QString rech=ui->lineEdit_rechercher->text();
        ui->tableViewr->setModel(R.recherche(rech));

}

void MainWindow::on_pushButton_PDFr_clicked()
{
    QPdfWriter pdf("C:\\Users\\rhy16\\OneDrive\\Desktop\\Integration\\PDF_ressource.pdf");

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

void MainWindow::on_pushButton_7r_clicked()
{
    //stat

            // Query the database to get the number of active and pending collaborators
            QSqlQuery query;
            query.prepare("SELECT COUNT(*) FROM RESSOURCE_LIBRARY WHERE RTYPE = 'Book'");
            query.exec();
            query.next();
            int BookCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM RESSOURCE_LIBRARY WHERE RTYPE = 'Article'");
            query.exec();
            query.next();
            int ArticleCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM RESSOURCE_LIBRARY WHERE RTYPE = 'Magazine'");
            query.exec();
            query.next();
            int MagazineCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM RESSOURCE_LIBRARY WHERE RTYPE = 'Online'");
            query.exec();
            query.next();
            int OnlineCount = query.value(0).toInt();

            query.prepare("SELECT COUNT(*) FROM RESSOURCE_LIBRARY WHERE RTYPE = 'Retailer'");
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




