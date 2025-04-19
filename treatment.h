#ifndef TREATMENT_H
#define TREATMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QComboBox>
#include <QDate>
class Treatment
{

QString  TNAME,TYPEE,DOSAGE ;
int TCOST;
QDate START_DATE,END_DATE ;
int ID_TREATMENT,ID_EMPLOYEE;

public:

  //Constructors
  Treatment(){}
  Treatment(int ID_TREATMENT , QString TNAME, QDate START_DATE, QDate END_DATE,QString TYPEE, QString DOSAGE, int TCOST, int ID_EMPLOYEE);

  //Getters
  QString getTNAME(){return  TNAME;}
  QDate getSTARTDATE(){return  START_DATE;}
  QDate getENDDATE(){return  END_DATE;}
  QString getTYPEE(){return  TYPEE;}
  QString getDOSAGE(){return  DOSAGE;}
  int getTCOST(){return TCOST;}

  int getID(){return  ID_TREATMENT;}
  int getID_EMPLOYEE(){return  ID_EMPLOYEE;}


  //Setters
  void setTNAME(QString n){TNAME=n;}
  void setSTARTDATE(QDate sd){START_DATE=sd;}
  void setENDDATE(QDate ed){END_DATE=ed;}
  void settypee(QString t){TYPEE=t;}
  void setDOSAGE(QString d){DOSAGE=d;}
  void setTCOST(int c){TCOST=c;}

  void setID(int ID_TREATMENT){this->ID_TREATMENT=ID_TREATMENT;}
  void setID_EMPLOYEE(int ID_EMPLOYEE){this->ID_EMPLOYEE=ID_EMPLOYEE;}

  // CRUD
  bool Create ();
  QSqlQueryModel * Read ();
  bool Delete (int ID_TREATMENT);
  bool update ();

  //COMBO BOX FOREIGN KEY
QSqlQueryModel* display();
void populateComboBox(QComboBox *lineEdit_ID);

//BASIC FEATURE : SORT
 QSqlQueryModel * sorttype();
 QSqlQueryModel * sortcost();
 QSqlQueryModel * sortdosage();

 //BASIC FEATURE : SEARCH
 QSqlQueryModel * recherchet(QString recherche);
};

#endif // TREATMENT_H


