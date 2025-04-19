#include "CONNECTION.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("anas");// insert the name of data source ODBC
    db.setUserName("AnasG");//insert username
    db.setPassword("esprit2022");//insert passeword

    if (db.open())  test = true ;

        return  test;
    return true;
}

void Connection::closeConnection(){ db.close(); }
