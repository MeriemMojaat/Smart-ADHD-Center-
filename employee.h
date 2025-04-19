#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>

class Employee
{
    int ID_EMPLOYEE;
    QString EFIRST_NAME , ELAST_NAME ,EGENDER , ROLES , DIPLOMAS , EPASSWORD , IDCARD;
    QDate EDOB;



public:
    //CONSTRUCTORS
    Employee(){};
    Employee(int ID_EMPLOYEE, QString EFIRST_NAME  ,QString ELAST_NAME, QString EGENDER  ,QString ROLES , QDate EDOB ,QString DIPLOMAS , QString EPASSWORD , QString IDCARD);
    //GETTERS
    QString getEFIRST_NAME();
    QString getELAST_NAME();
    QString getEGENDER();
    QString getROLES();
    QString getDIPLOMAS();
    QString getEPASSWORD();
    int getID_EMPLOYEE();
    QDate getDOB();

    //SETTERS
    void setID_EMPLOYEE(int ID_EMPLOYEE) ;
    void setEFIRST_NAME(QString EFIRST_NAME) ;
    void setELAST_NAME(QString ELAST_NAME) ;
    void setEGENDER(QString EGENDER);
    void setROLES(QString ROLES);
    void setDIPLOMAS(QString DIPLOMAS);
    void setDOB(QDate EDOB);
    void setEPASSWORD(QString EPASSWORD);


    // employee based features
    bool Create ();
    QSqlQueryModel * Read ();
    bool Delete (int ID_EMPLOYEE);
    bool Update();

    QSqlQueryModel * sortgender();
    QSqlQueryModel * sortrole();
    QSqlQueryModel * sortdiploma();

    QSqlQueryModel * recherche(QString recherche);
};

#endif // EMPLOYEE_H
