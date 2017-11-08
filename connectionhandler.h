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
    void newParametersRect(qreal x, qreal y);

public slots:
    void reconnectToHost();

protected:
    void sendToIRS(QByteArray data);

private slots:
    void IRSConnected();
    void IRSDisconnected();
    void IRSError(QAbstractSocket::SocketError);
    void IRSReadyRead();

private:

    QTcpSocket *IRServerSocket;
    QString IRS_IP;
    int IRS_port;
    bool isConnectedToIRS;
    QByteArray availableData;
};

#endif // CONNECTIONHANDLER_H
