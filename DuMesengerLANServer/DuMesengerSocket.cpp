#include "DuMesengerSocket.h"
namespace DuarteCorporation
{
DuMesengerSocket::DuMesengerSocket(qintptr handle, QObject *parent)
    : QTcpSocket(parent)
{
    setSocketDescriptor(handle);
    connect (this, &DuMesengerSocket::readyRead, [&](){
        emit DuReadyRead(this);
    });
    connect(this, &DuMesengerSocket::stateChanged, [&](int S){
        emit DuStateChanged(this, S);
    });
}
}
