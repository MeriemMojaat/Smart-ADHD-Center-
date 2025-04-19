#include "event.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlError>

event::event(int id_event,QString ename,QString place,QString etype,QString goals,QDate edate,int enbguests,int id_employee)
{
    this->id_event=id_event;
    this->ename=ename;
    this-> place=place;
     this-> etype=etype;
     this-> goals=goals;
    this->  edate= edate;
     this-> enbguests=enbguests;
     this->  id_employee= id_employee;


}

bool event::Create()
{
    QSqlQuery  query;

    QString res = QString::number(id_event);

    //prepare() takes the query as a parameter to prepare it for execution
    query.prepare("insert into event (id_event, ename, place, etype,goals,edate,enbguests,id_employee)" "values (:id_event, :ename, :place, :etype, :goals, :edate, :enbguests, (SELECT ID_EMPLOYEE FROM Employee WHERE ID_EMPLOYEE=:id_employee))");

    // Creating variables
    query.bindValue(":id_event",res);
    query.bindValue(":ename",ename);
    query.bindValue(":place",place);
     query.bindValue(":etype",etype);
   query.bindValue(":goals",goals);
     query.bindValue(":edate",edate);
    query.bindValue(":enbguests",enbguests);
    query.bindValue(":id_employee",id_employee);


    return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * event::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from event");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Place"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("Goals"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("Nbguests"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("id_employee"));


    return  model;
}

bool event::Delete(int id_event)
{
    QSqlQuery query;
    QString res=QString::number(id_event);

    query.prepare("delete from event where id_event= :id_event");

    query.bindValue(":id_event",res);

    return  query.exec();

}

bool event::update()
   {
   bool execStatus = false;
   QSqlQuery query;

       QString res=QString::number(id_event);


         QSqlQuery queryr;


         QSqlQueryModel *modelr= new QSqlQueryModel();


         queryr.prepare("SELECT * FROM event WHERE (id_event  LIKE "+res+")");


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
   QString res=QString::number(id_event);

   query.prepare("UPDATE event SET id_event=:id_event ,ename=:ename ,place=:place ,etype=:etype ,goals=:goals ,edate=:edate ,enbguests=:enbguests  ,id_employee=:id_employee WHERE id_event=:id_event");

   query.bindValue(":id_event",res);
   query.bindValue(":ename",ename);
   query.bindValue(":place",place);
   query.bindValue(":etype",etype);
  query.bindValue(":goals",goals);
    query.bindValue(":edate",edate);
   query.bindValue(":enbguests",enbguests);
   query.bindValue(":id_employee",id_employee);



   execStatus = query.exec();
   if (query.lastError().isValid()) {
       qDebug() << "Error: " << query.lastError().text();
   }
         }

         return execStatus;}

QSqlQueryModel* event::sortName()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from event ORDER BY ename ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Place"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Goals"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Nbguests"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("id_employee"));


return model;
}

QSqlQueryModel* event::sortNbguests()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from event ORDER BY enbguests ASC");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Place"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Goals"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Nbguests"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("id_employee"));



return model;
}

QSqlQueryModel* event::sortPlace()
{

QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select * from event ORDER BY place ASC");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Place"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Goals"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Nbguests"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("id_employee"));

 return model;
}

QSqlQueryModel* event::recherche(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM event WHERE id_event LIKE '"+recherche+"%' OR place LIKE '"+recherche+"%' OR ename LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Place"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("Goals"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("Nbguests"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("id_employee"));
      return model;
}
