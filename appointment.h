#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QComboBox>
#include <QDate>
class Appointment
{

  QString  APLACE, ADESCRIPTION, ATYPE ;
  QDate ADATE ;
  int ID_APPOINTMENT,ID_EMPLOYEE,ID_PATIENT;

public:

    //Constructors
    Appointment(){}
    Appointment(int ID_APPOINTMENT , QString APLACE, QString ADESCRIPTION, QString ATYPE,QDate ADATE, int ID_EMPLOYEE, int ID_PATIENT);

    //Getters
    QDate getADATE(){return  ADATE;}
    QString getAPLACE(){return  APLACE;}
    QString getADESCRIPTION(){return  ADESCRIPTION;}
    QString getATYPE(){return  ATYPE;}
    int getID(){return  ID_APPOINTMENT;}
    int getID_EMPLOYEE(){return  ID_EMPLOYEE;}
    int getID_PATIENT(){return  ID_PATIENT;}


    //Setters
    void setADATE(QDate n){ADATE=n;}
    void setAPLACE(QString p){APLACE=p;}
     void setADESCRIPTION(QString d){ADESCRIPTION=d;}
      void setATYPE(QString tapp){ATYPE=tapp;}

    void setID(int ID_APPOINMTENT){this->ID_APPOINTMENT=ID_APPOINMTENT;}
    void setID_PATIENT(int ID_PATIENT){this->ID_PATIENT=ID_PATIENT;}
    void setID_EMPLOYEE(int ID_EMPLOYEE){this->ID_EMPLOYEE=ID_EMPLOYEE;}

    //CRUD
    bool Create ();
    QSqlQueryModel * Read ();
    bool Delete (int ID_APPOINTMENT);
    bool update ();
    //
    QSqlQueryModel* display();
    void populateComboBox(QComboBox *lineEdit_ID);

    //ADVANCED FEATURES
    QSqlQueryModel* recherche(QString recherche);
    QSqlQueryModel* sortADATE();
    QSqlQueryModel* sortAPLACE();
    QSqlQueryModel* sortATYPE();
};

#endif // Appointment_H


