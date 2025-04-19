#include "treatment.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlError>



Treatment::Treatment(int ID_TREATMENT , QString TNAME, QDate START_DATE, QDate END_DATE,QString TYPEE, QString DOSAGE, int TCOST, int ID_EMPLOYEE)
{
   this->ID_TREATMENT =ID_TREATMENT ;
   this->TNAME=TNAME;
   this->START_DATE=START_DATE;
   this->END_DATE=END_DATE;
   this->TYPEE=TYPEE;
   this->DOSAGE=DOSAGE;
   this->TCOST=TCOST;
   this->ID_EMPLOYEE=ID_EMPLOYEE;




}

bool Treatment::Create()
{
   QSqlQuery  query;

   QString res = QString::number(ID_TREATMENT);

   //prepare() takes the query as a parameter to prepare it for execution
   query.prepare("INSERT INTO TREATMENT (ID_TREATMENT, TNAME, START_DATE, END_DATE, TYPEE, DOSAGE, TCOST, ID_EMPLOYEE)" "values (:ID_TREATMENT, :TNAME, :START_DATE, :END_DATE, :TYPEE, :DOSAGE, :TCOST,(SELECT ID_EMPLOYEE FROM Employee WHERE ID_EMPLOYEE=:ID_EMPLOYEE) )");

   // Creating variables
   query.bindValue(":ID_TREATMENT",res);
   query.bindValue(":TNAME",TNAME);
    query.bindValue(":START_DATE",START_DATE);
   query.bindValue(":END_DATE",END_DATE);
   query.bindValue(":TYPEE",TYPEE);
   query.bindValue(":DOSAGE",DOSAGE);
   query.bindValue(":TCOST",TCOST);
   query.bindValue(":ID_EMPLOYEE",ID_EMPLOYEE);


   return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * Treatment::Read()
{
   QSqlQueryModel * model=new QSqlQueryModel();

   model->setQuery("select * from Treatment");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TREATMENT"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("TNAME"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("START_DATE"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("END_DATE"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPEE"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("DOSAGE"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("TCOST"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));

   return  model;
}

bool Treatment::Delete(int ID_TREATMENT)
{
   QSqlQuery query;
   QString res=QString::number(ID_TREATMENT);

   query.prepare("Delete from Treatment where ID_TREATMENT= :ID_TREATMENT");

   query.bindValue(":ID_TREATMENT",res);

   return  query.exec();

}
bool Treatment::update()
   {
   bool execStatus = false;
   QSqlQuery query;

       QString res=QString::number(ID_TREATMENT);


         QSqlQuery queryr;


         QSqlQueryModel *modelr= new QSqlQueryModel();


         queryr.prepare("SELECT * FROM Treatment WHERE (ID_TREATMENT  LIKE "+res+")");


         if(queryr.exec()){
         modelr->setQuery(queryr);
         }


     if(queryr.exec()){
     modelr->setQuery(queryr);
     }


         if(queryr.numRowsAffected()==0){
            QMessageBox::warning(nullptr, QObject::tr("database is open"),
                        QObject::tr("Treatment not found .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

       }

         else{

   QSqlQuery query;
   QString res=QString::number(ID_TREATMENT);

   query.prepare("UPDATE Treatment SET TNAME=:TNAME ,START_DATE=:START_DATE ,END_DATE=:END_DATE ,TYPEE=:TYPEE ,DOSAGE=:DOSAGE ,TCOST=:TCOST ,ID_EMPLOYEE=:ID_EMPLOYEE WHERE ID_TREATMENT=:ID_TREATMENT");

   query.bindValue(":ID_TREATMENT",res);
   query.bindValue(":TNAME",TNAME);
    query.bindValue(":START_DATE",START_DATE);
   query.bindValue(":END_DATE",END_DATE);
   query.bindValue(":TYPEE",TYPEE);
   query.bindValue(":DOSAGE",DOSAGE);
   query.bindValue(":TCOST",TCOST);
   query.bindValue(":ID_EMPLOYEE",ID_EMPLOYEE);



   execStatus = query.exec();
   if (query.lastError().isValid()) {
       qDebug() << "Error: " << query.lastError().text();
   }
         }

         return execStatus;
   }
/*QSqlQueryModel* Treatment::display()
{
   QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select * from Treatment");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TREATMENT"));


   return model;



}
void populateComboBox(QComboBox *lineEdit_ID)
{ QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("source_project2A");
    db.setUserName("MeriemM");
    db.setPassword("esprit2022");



   QSqlQuery query("SELECT id_employee FROM employee ");
   lineEdit_ID->clear();
   while (query.next()) {
       int ID_EMPLOYEE = query.value(0).toInt();
       QString str_id = QString::number(ID_EMPLOYEE);
       lineEdit_ID->addItem(str_id);
   }

   db.close();
}*/

// Basic Features
    //Sort

QSqlQueryModel *Treatment::sorttype()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Treatment ORDER BY TYPEE");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TREATMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TNAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("START_DATE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("END_DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPEE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DOSAGE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TCOST"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));

    return model;
}

QSqlQueryModel *Treatment::sortcost()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Treatment ORDER BY TCOST ASC");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TREATMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TNAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("START_DATE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("END_DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPEE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DOSAGE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TCOST"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));

    return model;
}

QSqlQueryModel *Treatment::sortdosage()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Treatment ORDER BY DOSAGE DESC");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TREATMENT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TNAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("START_DATE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("END_DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPEE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DOSAGE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TCOST"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
     return model;
}

  //Search


QSqlQueryModel* Treatment::recherchet(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Treatment WHERE ID_TREATMENT LIKE '"+recherche+"%' OR TCOST LIKE '"+recherche+"%' OR TNAME LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_TREATMENT"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("TNAME"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("START_DATE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("END_DATE"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("TYPEE"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("DOSAGE"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("TCOST"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("ID_EMPLOYEE"));
      return model;
}

