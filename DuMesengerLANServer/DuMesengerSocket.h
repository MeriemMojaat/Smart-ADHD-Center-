#ifndef DUMESENGERSOCKET_H
#define DUMESENGERSOCKET_H
#include <QTcpSocket>
namespace DuarteCorporation
{
class DuMesengerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    DuMesengerSocket(qintptr handle,QObject *parent = nullptr);
signals:
    void DuReadyRead(DuMesengerSocket *);
    void DuStateChanged(DuMesengerSocket *,int);
};
}

#endif // DUMESENGERSOCKET_H
