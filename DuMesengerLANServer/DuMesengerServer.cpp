#include "DuMesengerServer.h"
#include "DuMesengerSocket.h"
#include <QTextStream>
#include <QDebug>
namespace DuarteCorporation
{
DuMesengerServer::DuMesengerServer(QObject *parent)
    :QTcpServer(parent)
{
}

bool DuMesengerServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);
}
void DuMesengerServer::incomingConnection(qintptr handle)
{
    qDebug() << "employe connected with handle : " << handle;

    auto socket = new DuMesengerSocket(handle , this);
    mSockets << socket ;

    for(auto i : mSockets){
        QTextStream T(i);
        T << "Server : il a connecté :" << handle;
        i->flush();
    }
    connect(socket, &DuMesengerSocket::DuReadyRead, [&](DuMesengerSocket *S){
        qDebug() << "DuReadyRead";
        QTextStream T(S);
        auto text = T.readAll();
        for(auto i : mSockets)
        {
             QTextStream K(i);
             K << text;
             i->flush();
        }
    });
    connect(socket, &DuMesengerSocket::DuStateChanged,
             [&](DuMesengerSocket *S, int ST){
        qDebug() << "DuStateChanged with handle : "
                 << S->socketDescriptor();

        if (ST == QTcpSocket::UnconnectedState)
        {
            qDebug() << "Unconnected State with handle "
                     << S->socketDescriptor();

            mSockets.removeOne(S);
            for(auto i :mSockets)
            {
                QTextStream K(i);
                K <<"Server : du client "
                 << S->socketDescriptor()
                 <<"il a déconnecté ...";
                i->flush();


            }
        }
    });
}
}
