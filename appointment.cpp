#include "appointment.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlError>



Appointment::Appointment(int ID_APPOINTMENT,QString APLACE,QString ADESCRIPTION,QString ATYPE,QDate ADATE,int ID_EMPLOYEE, int ID_PATIENT)

{
    this->ID_APPOINTMENT=ID_APPOINTMENT;
    this->APLACE=APLACE;
    this->ADESCRIPTION=ADESCRIPTION;
    this->ATYPE=ATYPE;
     this->ADATE=ADATE;
    this->ID_EMPLOYEE=ID_EMPLOYEE;
    this->ID_PATIENT=ID_PATIENT;



}

bool Appointment::Create()
{
    QSqlQuery  query;

    QString res = QString::number(ID_APPOINTMENT);

    //prepare() takes the query as a parameter to prepare it for execution
    query.prepare("insert into Appointment (ID_APPOINTMENT, APLACE, ADESCRIPTION, ATYPE, ADATE, ID_PATIENT,ID_EMPLOYEE )" "values (:ID_APPOINTMENT, :APLACE, :ADESCRIPTION, :ATYPE, :ADATE, (SELECT ID_PATIENT FROM Patient WHERE ID_PATIENT=:ID_PATIENT), (SELECT ID_EMPLOYEE FROM Employee WHERE ID_EMPLOYEE=:ID_EMPLOYEE))");

    // Creating variables
    query.bindValue(":ID_APPOINTMENT",res);
    query.bindValue(":APLACE",APLACE);
     query.bindValue(":ADESCRIPTION",ADESCRIPTION);
    query.bindValue(":ATYPE",ATYPE);
    query.bindValue(":ADATE",ADATE);
    query.bindValue(":ID_PATIENT",ID_PATIENT);
    query.bindValue(":ID_EMPLOYEE",ID_EMPLOYEE);





    return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * Appointment::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Appointment");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_APPOINTMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ADATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("APLACE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADESCRIPTION"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ATYPE"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_PATIENT"));


    return  model;
}

bool Appointment::Delete(int ID_APPOINTMENT)
{
    QSqlQuery query;
    QString res=QString::number(ID_APPOINTMENT);

    query.prepare("Delete from Appointment where ID_APPOINTMENT= :ID_APPOINTMENT");

    query.bindValue(":ID_APPOINTMENT",res);

    return  query.exec();

}
bool Appointment::update()
    {
    bool execStatus = false;
    QSqlQuery query;

        QString res=QString::number(ID_APPOINTMENT);


          QSqlQuery queryr;


          QSqlQueryModel *modelr= new QSqlQueryModel();


          queryr.prepare("SELECT * FROM Appointment WHERE (ID_APPOINTMENT  LIKE "+res+")");







          if(queryr.exec()){
          modelr->setQuery(queryr);
          }


      if(queryr.exec()){
      modelr->setQuery(queryr);
      }



          if(queryr.numRowsAffected()==0){
             QMessageBox::warning(nullptr, QObject::tr("database is open"),
                         QObject::tr("Appointment not found .\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);


        }



          else{

    QSqlQuery query;
    QString res=QString::number(ID_APPOINTMENT);

    query.prepare("UPDATE Appointment SET APLACE=:APLACE ,ADESCRIPTION=:ADESCRIPTION ,ATYPE=:ATYPE ,ADATE=:ADATE ,ID_EMPLOYEE=:ID_EMPLOYEE ,ID_PATIENT=:ID_PATIENT WHERE ID_APPOINTMENT=:ID_APPOINTMENT");

   query.bindValue(":ID_APPOINTMENT",ID_APPOINTMENT);
        query.bindValue(":APLACE",APLACE);
        query.bindValue(":ADESCRIPTION",ADESCRIPTION);
        query.bindValue(":ATYPE",ATYPE);
        query.bindValue(":ADATE",ADATE);
           query.bindValue(":ID_EMPLOYEE",ID_EMPLOYEE);
           query.bindValue(":ID_PATIENT",ID_PATIENT);

          /* query.bindValue(":ID_APPOINTMENT",1);
               query.bindValue(":APLACE","kkk");
               query.bindValue(":ADESCRIPTION","jjj");
               query.bindValue(":ATYPE","ATYPE");
               query.bindValue(":ADATE",ADATE);
                  query.bindValue(":ID_EMPLOYEE",0);
                  query.bindValue(":ID_PATIENT",0);*/


    execStatus = query.exec();
    if (query.lastError().isValid()) {
        qDebug() << "Error: " << query.lastError().text();
    }
          }

          return execStatus;
    }
QSqlQueryModel* Appointment::display()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM Appointment");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_APPOINTMENT"));



    return model;



}
void populateComboBox(QComboBox *lineEdit_ID)
{ QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("source_project2A");// insert the name of data source ODBC
    db.setUserName("Jawher");//insert username
    db.setPassword("esprit2022");//insert passeword


    QSqlQuery query("SELECT ID_EMPLOYEE FROM EMPLOYEE ");
    lineEdit_ID->clear();
    while (query.next()) {
        int ID_EMPLOYEE = query.value(0).toInt();
        QString str_id = QString::number(ID_EMPLOYEE);
        lineEdit_ID->addItem(str_id);
    }

    db.close();
}


QSqlQueryModel *Appointment::sortADATE()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Appointment ORDER BY ADATE DESC");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_APPOINTMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ADATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("APLACE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADESCRIPTION"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ATYPE"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_PATIENT"));


    return model;
}

QSqlQueryModel *Appointment::sortAPLACE()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Appointment ORDER BY APLACE ASC");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_APPOINTMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ADATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("APLACE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADESCRIPTION"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ATYPE"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_PATIENT"));


    return model;
}

QSqlQueryModel *Appointment::sortATYPE()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Appointment ORDER BY ATYPE");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_APPOINTMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ADATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("APLACE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADESCRIPTION"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ATYPE"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_PATIENT"));

     return model;
}

  //Search


QSqlQueryModel* Appointment::recherche(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Appointment WHERE ID_APPOINTMENT LIKE '"+recherche+"%' OR APLACE LIKE '"+recherche+"%' OR ATYPE LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_APPOINTMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("ADATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("APLACE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADESCRIPTION"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ATYPE"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_PATIENT"));

      return model;
}




