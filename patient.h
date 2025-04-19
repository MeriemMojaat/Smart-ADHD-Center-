#ifndef PATIENT_H
#define PATIENT_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>

class patient
{

  QString first_name, last_name, gender, address,email,typeofdiag;
  int id_patient, pnumber;
  QDate pdob;

public:

    //Constructors
    patient(){}
    patient(int id_patient,QString first_name,QString last_name,QDate pdob,QString gender,QString email,QString address,QString typeofdiag,int pnumber);

    //Getters
    int getID(){return  id_patient;}
    QString getfname(){return  first_name;}
    QString getlname(){return last_name;}
    QDate getdob(){return pdob;}
     QString getgender(){return  gender;}
      QString getemail(){return  email;}
      QString getaddress(){return address;}
      QString gettype(){return typeofdiag;}
      int getnumber(){return pnumber;}


    //Setters
      void setID(int id){this->id_patient=id;}
    void setfname(QString n){first_name=n;}
    void setlname(QString p){last_name=p;}
    void setdob(QDate a){pdob=a;}
    void setgender(QString b){gender=b;}
    void setemail(QString m){email=m;}
    void setaddress(QString ad){address=ad;}
    void settype(QString t){typeofdiag=t;}
    void setnumber(int nb){this->pnumber =nb;}

    //  base features
    bool Create ();
    QSqlQueryModel * Read ();
    bool Delete (int id_patient);
    bool update ();
 QSqlQueryModel* display();
 QSqlQueryModel* sortName();
 QSqlQueryModel* sortgender();
 QSqlQueryModel* sorttype();
 QSqlQueryModel* recherchep(QString recherche);

};

#endif


