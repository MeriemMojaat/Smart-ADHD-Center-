#include "patient.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlError>


patient:: patient(int id_patient,QString first_name,QString last_name,QDate pdob,QString gender,QString email,QString address,QString typeofdiag,int pnumber)
{
    this->id_patient=id_patient;
    this->first_name=first_name;
    this->last_name=last_name;
     this->pdob=pdob;
     this->gender=gender;
    this->email= email;
     this->address=address;
     this->typeofdiag= typeofdiag;
     this->pnumber=pnumber;


}

bool patient::Create()
{
    QSqlQuery  query;

    QString res = QString::number(id_patient);

    //prepare() takes the query as a parameter to prepare it for execution
    query.prepare("insert into patient (id_patient, first_name, last_name, pdob,gender,email,address,typeofdiag,pnumber)" "values (:id_patient, :first_name, :last_name, :pdob, :gender, :email, :address, :typeofdiag, :pnumber)");

    // Creating variables
    query.bindValue(":id_patient",res);
    query.bindValue(":first_name",first_name);
    query.bindValue(":last_name",last_name);
     query.bindValue(":pdob",pdob);
   query.bindValue(":gender",gender);
     query.bindValue(":email",email);
    query.bindValue(":address",address);
    query.bindValue(":typeofdiag",typeofdiag);
    query.bindValue(":pnumber",pnumber);


    return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * patient::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from patient");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Fname"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Lname"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("DOB"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("Gender"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("Email"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("Address"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type"));
       model->setHeaderData(8,Qt::Horizontal,QObject::tr("Pnumber"));


    return  model;
}

bool patient::Delete(int id_patient)
{
    QSqlQuery query;
    QString res=QString::number(id_patient);

    query.prepare("delete from patient where id_patient= :id_patient");

    query.bindValue(":id_patient",res);

    return  query.exec();

}

bool patient::update()
   {
   bool execStatus = false;
   QSqlQuery query;

       QString res=QString::number(id_patient);


         QSqlQuery queryr;


         QSqlQueryModel *modelr= new QSqlQueryModel();


         queryr.prepare("SELECT * FROM patient WHERE (id_patient  LIKE "+res+")");


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
   QString res=QString::number(id_patient);

   query.prepare("UPDATE patient SET id_patient=:id_patient ,first_name=:first_name ,last_name=:last_name ,pdob=:pdob ,gender=:gender ,email=:email ,address=:address  ,typeofdiag=:typeofdiag ,pnumber=:pnumber WHERE id_patient=:id_patient");

   query.bindValue(":id_patient",res);
   query.bindValue(":first_name",first_name);
   query.bindValue(":last_name",last_name);
    query.bindValue(":pdob",pdob);
  query.bindValue(":gender",gender);
    query.bindValue(":email",email);
   query.bindValue(":address",address);
   query.bindValue(":typeofdiag",typeofdiag);
   query.bindValue(":pnumber",pnumber);



   execStatus = query.exec();
   if (query.lastError().isValid()) {
       qDebug() << "Error: " << query.lastError().text();
   }
         }

         return execStatus;
   }
QSqlQueryModel* patient::display()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM patient");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_patient"));



    return model;

}

//Sort

QSqlQueryModel* patient::sortName()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from patient ORDER BY first_name ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Fname"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Lname"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("DOB"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Gender"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Email"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Address"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("Pnumber"));


return model;
}

QSqlQueryModel* patient::sortgender()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from patient ORDER BY gender ASC");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Fname"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Lname"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("DOB"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Gender"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Email"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Address"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("Pnumber"));



return model;
}

QSqlQueryModel* patient::sorttype()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from patient ORDER BY typeofdiag ASC");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Fname"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Lname"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("DOB"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Gender"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Email"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Address"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("Pnumber"));
 return model;
}

//Search


QSqlQueryModel* patient::recherchep(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Patient WHERE ID_PATIENT LIKE '"+recherche+"%' OR PDOB LIKE '"+recherche+"%' OR ADDRESS LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Fname"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Lname"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("DOB"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Gender"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Email"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Address"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("Type"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("Pnumber"));
      return model;
}





