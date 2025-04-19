#include "employee.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlError>
Employee::Employee(int ID_EMPLOYEE, QString EFIRST_NAME  ,QString ELAST_NAME, QString EGENDER  ,QString ROLES , QDate EDOB,QString DIPLOMAS, QString EPASSWORD , QString IDCARD  )
{
    this->ID_EMPLOYEE = ID_EMPLOYEE;
    this->EFIRST_NAME = EFIRST_NAME;
    this->ELAST_NAME = ELAST_NAME;
    this->EGENDER = EGENDER;
    this->ROLES = ROLES;
    this->EDOB = EDOB;
    this->DIPLOMAS = DIPLOMAS;
    this->EPASSWORD = EPASSWORD;
    this->IDCARD = IDCARD;

}

bool Employee::Create()
{
    QSqlQuery query;

    QString res = QString::number(ID_EMPLOYEE);


    // prepare() takes the query as a parameter to prepare it for execution
    query.prepare("INSERT INTO Employee (ID_EMPLOYEE,EFIRST_NAME, ELAST_NAME, EGENDER, ROLES,EDOB, DIPLOMAS , EPASSWORD , IDCARD ) "
                  "VALUES (:ID_EMPLOYEE, :EFIRST_NAME, :ELAST_NAME, :EGENDER, :ROLES, :EDOB, :DIPLOMAS ,:EPASSWORD ,:IDCARD)");

    // bindValue() binds values to placeholders in the query
    query.bindValue(":ID_EMPLOYEE", res);
    query.bindValue(":EFIRST_NAME", EFIRST_NAME);
    query.bindValue(":ELAST_NAME", ELAST_NAME);
    query.bindValue(":EGENDER", EGENDER);
    query.bindValue(":ROLES", ROLES);
    query.bindValue(":DIPLOMAS", DIPLOMAS);
    query.bindValue(":EDOB", EDOB);
    query.bindValue(":EPASSWORD", EPASSWORD);
    query.bindValue(":IDCARD", IDCARD);


    // exec() sends the request to be executed and returns true if successful
    return query.exec();
}
bool Employee::Update()
{
    bool execStatus = false;
       QSqlQuery query;

           QString res=QString::number(ID_EMPLOYEE);


             QSqlQuery queryr;


             QSqlQueryModel *modelr= new QSqlQueryModel();


             queryr.prepare("SELECT * FROM Employee WHERE (ID_EMPLOYEE  LIKE "+res+")");


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
       QString res=QString::number(ID_EMPLOYEE);

       query.prepare("UPDATE Employee SET EFIRST_NAME=:EFIRST_NAME ,ELAST_NAME=:ELAST_NAME ,EGENDER=:EGENDER ,ROLES=:ROLES ,DIPLOMAS=:DIPLOMAS , EPASSWORD=:EPASSWORD , IDCARD=:IDCARD WHERE ID_EMPLOYEE=:ID_EMPLOYEE");

       // bindValue() binds values to placeholders in the query
       query.bindValue(":ID_EMPLOYEE", res);
       query.bindValue(":EFIRST_NAME", EFIRST_NAME);
       query.bindValue(":ELAST_NAME", ELAST_NAME);
       query.bindValue(":EGENDER", EGENDER);
       query.bindValue(":ROLES", ROLES);
       query.bindValue(":DIPLOMAS", DIPLOMAS);
       query.bindValue(":EDOB", EDOB);
       query.bindValue(":EPASSWORD", EPASSWORD);
       query.bindValue(":IDCARD", IDCARD);



       execStatus = query.exec();
       if (query.lastError().isValid()) {
           qDebug() << "Error: " << query.lastError().text();
       }
             }

             return execStatus;
}

bool Employee::Delete(int ID_EMPLOYEE) {
    QSqlQuery query;
    QString res = QString::number(ID_EMPLOYEE);

    query.prepare("DELETE FROM Employee WHERE ID_EMPLOYEE = :ID_EMPLOYEE");
    query.bindValue(":ID_EMPLOYEE", res);

    return query.exec();
}

QSqlQueryModel * Employee::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Employee");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id Employee"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Gender"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Roles"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date Of Birth"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Diplomas"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Password"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Id Card"));

    return  model;
}

QString Employee :: getEFIRST_NAME()
{return EFIRST_NAME;}

QString Employee :: getELAST_NAME()
{return ELAST_NAME;}
QString Employee :: getEGENDER()
{return EGENDER;}
QString Employee :: getROLES()
{return ROLES;}
QString Employee :: getDIPLOMAS()
{return DIPLOMAS;};
int  Employee :: getID_EMPLOYEE()
{return ID_EMPLOYEE;}
QDate Employee :: getDOB()
{return EDOB;}
QString Employee::getEPASSWORD()
{return EPASSWORD;}

//SETTERS
void  Employee :: setID_EMPLOYEE(int id)
{ID_EMPLOYEE = id;}
void Employee :: setEFIRST_NAME(QString fname)
{EFIRST_NAME = fname;}
void Employee :: setELAST_NAME(QString lname)
{ELAST_NAME = lname;}
void Employee :: setEGENDER(QString gen)
{EGENDER = gen;}
void Employee :: setROLES(QString rol)
{ROLES = rol;}
void Employee :: setDIPLOMAS(QString dip)
{DIPLOMAS = dip;}
void Employee :: setDOB(QDate dob)
{EDOB = dob;}
void Employee::setEPASSWORD(QString epass)
{EPASSWORD = epass;}

QSqlQueryModel * Employee::sortgender()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Employee ORDER BY EGENDER");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id Employee"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Gender"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Roles"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date Of Birth"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Diplomas"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Password"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Id Card"));

    return model;
}

QSqlQueryModel * Employee::sortrole()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Employee ORDER BY ROLES ASC");

    // set the headers for the columns of the QSqlQueryModel object

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id Employee"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Gender"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Roles"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date Of Birth"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Diplomas"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Password"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Id Card"));

    return model;
}

QSqlQueryModel * Employee::sortdiploma()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Employee ORDER BY DIPLOMAS");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id Employee"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Gender"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Roles"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date Of Birth"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Diplomas"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Password"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Id Card"));
     return model;
}


QSqlQueryModel * Employee::recherche(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM Employee WHERE ID_EMPLOYEE LIKE '"+recherche+"%' OR ROLES LIKE '"+recherche+"%' OR ELAST_NAME LIKE '"+recherche+"%'");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id Employee"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Gender"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Roles"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date Of Birth"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Diplomas"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("Password"));
     model->setHeaderData(8,Qt::Horizontal,QObject::tr("Id Card"));
      return model;
}

