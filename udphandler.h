#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include "connectionhandler.h"
#include <QAbstractSocket>
class QUdpSocket;
class QTcpSocket;
class QPixmap;

class UDPHandler : public ConnectionHandler
{
    Q_OBJECT
public:
    explicit UDPHandler(QObject *parent = nullptr);
    ~UDPHandler();

signals:

private slots:
    void readBytes();

public slots:

private:

    QUdpSocket *mobileClientSocket;


};

#endif // UDPHANDLER_H
