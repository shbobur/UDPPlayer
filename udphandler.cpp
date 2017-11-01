#include "udphandler.h"

#include <QUdpSocket>
#include <QTcpSocket>
#include <QPixmap>

#define PORT 6600

UDPHandler::UDPHandler(QObject *parent) : ConnectionHandler(parent)
{
    // set UDP socket to receive frames from mobile agent
    mobileClientSocket = new QUdpSocket(this);
    connect(mobileClientSocket, &QIODevice::readyRead, this, &UDPHandler::readBytes);

    if (mobileClientSocket->bind(PORT)) {
        qDebug() << QString("Bound to port %1\n").arg(PORT);
    } else {
        qDebug() << QString("Could not Bind to `port %1\n").arg(PORT);
    }

}

UDPHandler::~UDPHandler()
{
    if (mobileClientSocket->isOpen())
        mobileClientSocket->disconnect();
    mobileClientSocket->deleteLater();
}

void UDPHandler::readBytes()
{
    QByteArray datagram;

    //int size = client->pendingDatagramSize();
    do {
        //qDebug() << QString("Receiving %1 bytes").arg(client->pendingDatagramSize());
        datagram.resize(mobileClientSocket->pendingDatagramSize());
        mobileClientSocket->readDatagram(datagram.data(), datagram.size());
    } while (mobileClientSocket->hasPendingDatagrams());


    QPixmap pixmap;
    pixmap.loadFromData(datagram, "JPEG");
    //image.loadFromData(datagram, "JPEG");
    //if (!pixmap.isNull()) {
        emit newFrame(pixmap);
       // qDebug() << "Valid frame received";
    //} else
        //  qDebug() << "Cannot decode image\n";

    //sendToIRS(datagram);
}
