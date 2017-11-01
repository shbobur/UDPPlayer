#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QPixmap>
#include <QAbstractSocket>

class QTcpSocket;

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler(QObject *parent = nullptr);
    ~ConnectionHandler();


signals:
    void newFrame(QPixmap);

public slots:
    void reconnectToHost();

protected:
    void sendToIRS(QByteArray data);
    void sendToIRS(uchar* data, int len);

private slots:
    void IRSConnected();
    void IRSDisconnected();
    void IRSError(QAbstractSocket::SocketError);

private:

    QTcpSocket *IRServerSocket;
    QString IRS_IP;
    int IRS_port;
    bool isConnectedToIRS;
};

#endif // CONNECTIONHANDLER_H
