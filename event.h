#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>

class event
{

  QString ename, place, etype, goals;
  int id_event, enbguests, id_employee;
  QDate edate;

public:

    //Constructors
    event(){}
    event(int id_event,QString ename,QString place,QString etype,QString goals,QDate edate,int enbguests,int id_employee);

    //Getters
    int getID(){return  id_event;}
    QString getename(){return  ename;}
    QString getplace(){return  place;}
     QString getetype(){return  etype;}
      QString getgoals(){return  goals;}
      int getenbguests(){return enbguests;}
      int getidemployee(){return id_employee;}


    //Setters
      void setID(int id){this->id_event=id;}
    void setename(QString n){ename=n;}
    void setplace(QString p){place=p;}
    void setetype(QString a){etype=a;}
    void setgoals(QString b){goals=b;}
    void setedate(QDate m){edate=m;}
    void setenbguests(int nb){this->enbguests=nb;}
    void setidemployee(int idemp){this->id_employee=idemp;}

    //  base features
    bool Create ();
    QSqlQueryModel * Read ();
    bool Delete (int id_event);
    bool update ();
    QSqlQueryModel* sortName();
    QSqlQueryModel* sortPlace();
    QSqlQueryModel* sortNbguests();
    QSqlQueryModel* recherche(QString recherche);
};

#endif // EVENT_H
