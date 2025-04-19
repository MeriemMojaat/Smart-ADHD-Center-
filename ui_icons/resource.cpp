#include "resource.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlError>



resource::resource(int ID_RESSOURCE, QString TITLE, QString RLANGUAGE, QString RTYPE, QString RAVAILABILITY, QDate RDATE, QString RDESCRIPTION, int ID_EMPLOYEE)
{
    this->ID_RESSOURCE = ID_RESSOURCE;
    this->TITLE = TITLE;
    this->RLANGUAGE = RLANGUAGE;
    this->RTYPE = RTYPE;
    this->RAVAILABILITY = RAVAILABILITY;
    this->RDATE = RDATE;
    this->RDESCRIPTION = RDESCRIPTION;
    this->ID_EMPLOYEE = ID_EMPLOYEE;
}


bool resource::Create()
{
    QSqlQuery query;

    QString res = QString::number(ID_RESSOURCE);//nbadlouha men number li string

    //prepare() takes the query as a parameter to prepare it for execution
    query.prepare("insert into RESSOURCE_LIBRARY (ID_RESSOURCE, TITLE, RLANGUAGE, RTYPE, RAVAILABILITY, RDATE, RDESCRIPTION, ID_EMPLOYEE) values (:ID_RESSOURCE, :TITLE, :RLANGUAGE, :RTYPE, :RAVAILABILITY, :RDATE, :RDESCRIPTION,(SELECT ID_EMPLOYEE FROM Employee WHERE ID_EMPLOYEE=:ID_EMPLOYEE ) )");

    // retriving variables yekho el varaibles li ndakhlou fihom w yakrahom
    query.bindValue(":ID_RESSOURCE", res);
    query.bindValue(":TITLE", TITLE);
    query.bindValue(":RLANGUAGE", RLANGUAGE);
    query.bindValue(":RTYPE", RTYPE);
    query.bindValue(":RAVAILABILITY", RAVAILABILITY);
    query.bindValue(":RDATE", RDATE);
    query.bindValue(":RDESCRIPTION", RDESCRIPTION);
   query.bindValue(":ID_EMPLOYEE", ID_EMPLOYEE);

    return query.exec(); //exec() send request to be executed
}


QSqlQueryModel* resource::Read()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RESSOURCE_LIBRARY");//select all the attributes from database
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESSOURCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITLE"));//nhothohoum fit west e table view mteena
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RLANGUAGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RTYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("RAVAILABILITY"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("RDATE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("RDESCRIPTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_EMPLOYEE"));
    return model;
}


bool resource::Delete(int ID_RESSOURCE)
{
    QSqlQuery query;
    QString res=QString::number(ID_RESSOURCE);

    query.prepare("Delete from RESSOURCE_LIBRARY where ID_RESSOURCE= :ID_RESSOURCE");

    query.bindValue(":ID_RESSOURCE",res);//bech nekhou l value men line edit w nemchi nbadalha fi database

    return  query.exec();

}
bool resource::Update()
{
    bool execStatus = false;
       QSqlQuery query;

           QString res=QString::number(ID_RESSOURCE);


             QSqlQuery queryr;


             QSqlQueryModel *modelr= new QSqlQueryModel();


             queryr.prepare("SELECT * FROM RESSOURCE_LIBRARY WHERE (ID_RESSOURCE  LIKE "+res+")");


             if(queryr.exec()){
             modelr->setQuery(queryr);
             }


         if(queryr.exec()){
         modelr->setQuery(queryr);
         }


             if(queryr.numRowsAffected()==0){
                QMessageBox::warning(nullptr, QObject::tr("database is open"),
                            QObject::tr("not found .\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

           }

             else{

       QSqlQuery query;
       QString res=QString::number(ID_RESSOURCE);

       query.prepare("UPDATE RESSOURCE_LIBRARY SET TITLE=:TITLE ,RLANGUAGE=:RLANGUAGE ,RTYPE=:RTYPE ,RAVAILABILITY=:RAVAILABILITY ,RDATE=:RDATE ,RDESCRIPTION=:RDESCRIPTION,ID_EMPLOYEE=:ID_EMPLOYEE WHERE ID_RESSOURCE=:ID_RESSOURCE");

       query.bindValue(":ID_RESSOURCE", res);
       query.bindValue(":TITLE", TITLE);
       query.bindValue(":RLANGUAGE", RLANGUAGE);
       query.bindValue(":RTYPE", RTYPE);
       query.bindValue(":RAVAILABILITY", RAVAILABILITY);
       query.bindValue(":RDATE", RDATE);
       query.bindValue(":RDESCRIPTION", RDESCRIPTION);
      query.bindValue(":ID_EMPLOYEE", ID_EMPLOYEE);



       execStatus = query.exec();
       if (query.lastError().isValid()) {
           qDebug() << "Error: " << query.lastError().text();
       }
             }

             return execStatus;
}




/*
void populateComboBox(QComboBox *lineEdit_ID)
{ QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("anas");// insert the name of data source ODBC
    db.setUserName("anas");//insert username
    db.setPassword("0911827178");//insert passeword


    QSqlQuery query("SELECT ID_EMPLOYEE FROM employee ");//bech ijib el id lkol fil combobox mel bd
    lineEdit_ID->clear();
    while (query.next()) {
        int ID_EMPLOYEE = query.value(0).toInt();
        QString str_id = QString::number(ID_EMPLOYEE);
        lineEdit_ID->addItem(str_id);
    }

    db.close();
}

QSqlQueryModel* resource::display()//display combobox
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM resource");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));

    return model;

}
*/

QSqlQueryModel* resource::sorttype()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from RESSOURCE_LIBRARY ORDER BY RTYPE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESSOURCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITLE"));//nhothohoum fit west e table view mteena
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RLANGUAGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RTYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("RAVAILABILITY"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("RDATE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("RDESCRIPTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_EMPLOYEE"));

    return model;
}


QSqlQueryModel* resource::sortavailability()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from RESSOURCE_LIBRARY ORDER BY RAVAILABILITY");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESSOURCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITLE"));//nhothohoum fit west e table view mteena
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RLANGUAGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RTYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("RAVAILABILITY"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("RDATE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("RDESCRIPTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_EMPLOYEE"));

    return model;
}


QSqlQueryModel * resource::sortlanguage()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from RESSOURCE_LIBRARY ORDER BY RLANGUAGE");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESSOURCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITLE"));//nhothohoum fit west e table view mteena
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RLANGUAGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RTYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("RAVAILABILITY"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("RDATE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("RDESCRIPTION"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_EMPLOYEE"));
     return model;
}

  //Search



QSqlQueryModel* resource::recherche(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM RESSOURCE_LIBRARY WHERE ID_RESSOURCE LIKE '"+recherche+"%' OR TITLE LIKE '"+recherche+"%' OR RLANGUAGE LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RESSOURCE"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITLE"));//nhothohoum fit west e table view mteena
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("RLANGUAGE"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("RTYPE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("RAVAILABILITY"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("RDATE"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("RDESCRIPTION"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_EMPLOYEE"));
      return model;
}

