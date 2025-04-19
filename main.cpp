#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "authentication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c; //One unique instance  connection class

    bool test=c.createconnection();// create connexion

    MainWindow w;
    Authentication A;

    if(test) // case  - connection estblished
    {
        w.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else // connexion fail

        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
