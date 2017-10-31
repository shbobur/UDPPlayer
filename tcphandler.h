#ifndef TCPHANDLER_H
#define TCPHANDLER_H

#include "connectionhandler.h"
#include <QAbstractSocket>

class QTcpSocket;
class QTcpServer;

class TCPHandler : public ConnectionHandler
{
    Q_OBJECT
public:
    explicit TCPHandler(QObject *parent = nullptr);
    ~TCPHandler();

public slots:
    void reconnectToHost();

signals:

private slots:
    void receiveClientData();
    void clientConnected();
    void clientDiconnected();
    void errorHandle(QAbstractSocket::SocketError);


private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpConnection;
    QString IP;
    int port;

    bool tryToListen();
    void startListening();
    int incomingFrameLength;
};

#endif // TCPHANDLER_H
