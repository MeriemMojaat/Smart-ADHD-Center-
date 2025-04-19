#ifndef RESOURCE_H
#define RESOURCE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include <QComboBox>

class resource
{

    int ID_EMPLOYEE;
    QString TITLE, RLANGUAGE, RTYPE, RAVAILABLILITY, RDESCRIPTION;
    QDate RDATE;
    int ID_RESSOURCE;

public:
    // Constructors
    resource(){}
    resource(int ID_RESSOURCE, QString TITLE, QString RLANGUAGE, QString RTYPE, QString RAVAILABILITY, QDate RDATE, QString RDESCRIPTION, int ID_EMPLOYEE);

    // Getters
    int getID() { return ID_RESSOURCE; }
    QString getTITLE() { return TITLE; }
    QString getRLANGUAGE() { return RLANGUAGE; }
    QString getRTYPE() { return RTYPE; }
    QString getRAVAILABILITY() { return RAVAILABLILITY; }
    QDate getRDATE() { return RDATE; }
    QString getRDESCRIPTION() { return RDESCRIPTION; }
    int getID_EMPLOYEE() { return ID_EMPLOYEE; }

    // Setters
    void setID(int ID_RESSOURCE) { this->ID_RESSOURCE = ID_RESSOURCE; }
    void setTITLE(QString TITLE) { this->TITLE = TITLE; }
    void setRLANGUAGE(QString RLANGUAGE) { this->RLANGUAGE = RLANGUAGE; }
    void setRTYPE(QString RTYPE) { this->RTYPE = RTYPE; }
    void setRAVAILABILITY(QString RAVAILABLILITY) { this->RAVAILABLILITY = RAVAILABLILITY; }
    void setRDATE(QDate RDATE) { this->RDATE = RDATE; }
    void setRDESCRIPTION(QString RDESCRIPTION) { this->RDESCRIPTION = RDESCRIPTION; }


    // Resource base features
    bool Create();
    QSqlQueryModel * Read();
    bool Delete(int ID_RESSOURCE);
    bool Update();
     QSqlQueryModel * display();
     void populateComboBox(QComboBox *lineedit_id);

     QSqlQueryModel * sortavailability();
     QSqlQueryModel * sortlanguage();
     QSqlQueryModel * sorttype();
     QSqlQueryModel * recherche(QString recherche);
};
#endif

