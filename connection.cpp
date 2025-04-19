#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("source_project2A");// insert the name of data source ODBC
    db.setUserName("mohamed");//insert username
    db.setPassword("Kiki98765");//insert passeword

    if (db.open())  test = true ;

    return  test;
    return true;
}

void Connection::closeConnection(){ db.close(); }

