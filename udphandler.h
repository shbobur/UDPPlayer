#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include "connectionhandler.h"

class QUdpSocket;
class QPixmap;

class UDPHandler : public ConnectionHandler
{
    Q_OBJECT
public:
    explicit UDPHandler(QObject *parent = nullptr);
    ~UDPHandler();

signals:
    void newFrame(QPixmap);

private slots:
    void readBytes();

public slots:

private:

    QUdpSocket *client;

};

#endif // UDPHANDLER_H
