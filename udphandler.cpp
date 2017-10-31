#include "udphandler.h"

#include <QUdpSocket>
#include <QPixmap>

#define PORT 6600

UDPHandler::UDPHandler(QObject *parent) : ConnectionHandler(parent)
{
    client = new QUdpSocket(this);

    connect(client, &QIODevice::readyRead, this, &UDPHandler::readBytes);

    if (client->bind(PORT)) {
        qDebug() << QString("Bound to port %1\n").arg(PORT);
    } else {
        qDebug() << QString("Could not Bind to port %1\n").arg(PORT);
    }
}

UDPHandler::~UDPHandler()
{
    if (client->isOpen())
        client->disconnect();
    client->deleteLater();
}

void UDPHandler::readBytes()
{
    QByteArray datagram;

    //int size = client->pendingDatagramSize();
    do {
        //qDebug() << QString("Receiving %1 bytes").arg(client->pendingDatagramSize());
        datagram.resize(client->pendingDatagramSize());
        client->readDatagram(datagram.data(), datagram.size());
    } while (client->hasPendingDatagrams());


    QPixmap pixmap;
    pixmap.loadFromData(datagram, "JPEG");
    //image.loadFromData(datagram, "JPEG");
    if (!pixmap.isNull()) {
        emit newFrame(pixmap);
        qDebug() << "Valid frame received";
    } else
        qDebug() << "Cannot decode image\n";
}
