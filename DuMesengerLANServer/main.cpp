#include <QCoreApplication>
#include"DuMesengerServer.h"

using namespace DuarteCorporation;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DuMesengerServer Server;
    if(!Server.startServer(300)){
        qDebug() << "Error:" << Server.errorString();
        return 1;
    }
    qDebug() << "Server Started  ..." ;


    return a.exec();
}
