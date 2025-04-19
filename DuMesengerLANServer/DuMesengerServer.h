#ifndef DUMESENGERSERVER_H
#define DUMESENGERSERVER_H

#include <QTcpServer>
namespace DuarteCorporation
{
class DuMesengerSocket;
class DuMesengerServer: public QTcpServer
{
public:
    DuMesengerServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
protected:
    void incomingConnection(qintptr handle);
private:
    QList<DuMesengerSocket *>mSockets;
};
}//end namespace DuarteCorporation
#endif // DUMESENGERSERVER_H
