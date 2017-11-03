#include "connectionhandler.h"

#include <QTcpSocket>

ConnectionHandler::ConnectionHandler(QObject *parent) : QObject(parent)
{
    // all connections are established in subclasses.
    // IRS is common for all classes so its connection is created here (in base class)

    // set TCP socket to send frames to IRS (Image Recognition Server)
    IRS_IP = "192.168.101.127";// "192.168.101.118"; // 118
    IRS_port = 9999;  // 5599
    isConnectedToIRS = false;
    IRServerSocket = new QTcpSocket(this);
    connect(IRServerSocket, SIGNAL(connected()), SLOT(IRSConnected()));
    connect(IRServerSocket, SIGNAL(disconnected()), SLOT(IRSDisconnected()));
    connect(IRServerSocket, SIGNAL(readyRead()), SLOT(IRSReadyRead()));
    connect(IRServerSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(IRSError(QAbstractSocket::SocketError)));
    qDebug() << "Trying to connect to IR Server (" << IRS_IP << ":" << IRS_port << ")";
    IRServerSocket->connectToHost(this->IRS_IP, this->IRS_port);
}

ConnectionHandler::~ConnectionHandler()
{
    if (IRServerSocket->isOpen())
        IRServerSocket->close();
    IRServerSocket->deleteLater();
}

void ConnectionHandler::reconnectToHost()
{

}

void ConnectionHandler::IRSConnected()
{
    isConnectedToIRS = true;
    qDebug() << "Connected to IR Server";
}

void ConnectionHandler::IRSDisconnected()
{
    isConnectedToIRS = false;
    qDebug() << "Disconnected from IR Server";
    qDebug() << "Trying to connect to IR Server (" << IRS_IP << ":" << IRS_port << ")";
    IRServerSocket->connectToHost(IRS_IP, IRS_port);
}

void ConnectionHandler::IRSError(QAbstractSocket::SocketError error)
{
    qDebug() << "IRS connection error:" << IRServerSocket->errorString();
    //qDebug() << "Trying to connect to IR Server (" << IRS_IP << ":" << IRS_port << ")";
    //IRServerSocket->connectToHost(IRS_IP, IRS_port);
}

void ConnectionHandler::IRSReadyRead()
{
   /* QString ack = IRServerSocket->readAll();
    if (ack == "ok" && !availableData.isEmpty()) {
        IRServerSocket->write(availableData);
        availableData.clear();
    }*/
}

void ConnectionHandler::sendToIRS(QByteArray data)
{
    if (isConnectedToIRS) {
        QDataStream stream(IRServerSocket);
        int t = data.size();
        stream << t;
        IRServerSocket->waitForBytesWritten(3000);
        stream << data;
        IRServerSocket->waitForBytesWritten(3000);
        //availableData = data;
        qDebug() << "Sent a frame size of " << data.size() << " to IRS";
    }
}

