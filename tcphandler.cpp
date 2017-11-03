#include "tcphandler.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QWidget>
#include <QMessageBox>

TCPHandler::TCPHandler(QObject *parent) : ConnectionHandler(parent)
{
    IP = "127.0.0.1";
    port = 5900;

    tcpConnection = new QTcpSocket(this);
    tcpConnection->connectToHost(IP, port);
    //ui->sourceLineEdit->setText(tcpConnection->localAddress().toString() + "/" + QString::number(tcpConnection->localPort()));
    connect(tcpConnection, &QIODevice::readyRead, this, &TCPHandler::receiveClientData);
    connect(tcpConnection, &QAbstractSocket::disconnected, this, &TCPHandler::clientDiconnected);
    connect(tcpConnection, &QAbstractSocket::connected, this, &TCPHandler::clientConnected);
    connect(tcpConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorHandle(QAbstractSocket::SocketError)));
    qDebug() << "TCPHandler constructor";

    this->incomingFrameLength = 0;
}

TCPHandler::~TCPHandler()
{
    if (tcpConnection->isOpen())
        tcpConnection->disconnectFromHost();
    tcpConnection->deleteLater();
}

void TCPHandler::receiveClientData()
{
    if(this->incomingFrameLength==0){
        QString data = tcpConnection->readAll();
        this->incomingFrameLength = data.toInt();
        tcpConnection->write("ok");
       // qDebug()<<QString("Received frame length: %1").arg(this->incomingFrameLength);
        return;
    }

    if(this->incomingFrameLength!=0 && tcpConnection->bytesAvailable()<this->incomingFrameLength) {
       // qDebug() << tcpConnection->bytesAvailable() << " Return...";
        return;
    }

    uchar* data = (uchar*)malloc(this->incomingFrameLength+256);
    qint64 len = tcpConnection->read((char*)data, this->incomingFrameLength+256);

    //qDebug() << QString("Received %1 bytes").arg(len);
    QPixmap pixmap;
    pixmap.loadFromData(data, len, "JPEG");
    if (!pixmap.isNull()) {
        emit newFrame(pixmap);
        qDebug() << len;
        sendToIRS(QByteArray((char*)data, len));
        //qDebug() << "Pixmap was received succesfully";
    }
    else
        qDebug() << "Pixmap is null.";

    this->incomingFrameLength=0;
    tcpConnection->write("received");
    //qDebug()<<QString("Received frame of length %1").arg(len);

    free(data);

}

void TCPHandler::clientConnected()
{
    qDebug() << "Client is connected to " << tcpConnection->peerAddress()<< ":" << tcpConnection->peerPort();// tcpConnection->localPort();
}

void TCPHandler::clientDiconnected()
{
    qDebug() << "Disconnected.";
    reconnectToHost();
}

void TCPHandler::errorHandle(QAbstractSocket::SocketError)
{
    qDebug() << tcpConnection->errorString();
}

void TCPHandler::reconnectToHost()
{
    if (tcpConnection->isOpen())
        tcpConnection->close();
    tcpConnection->connectToHost(IP, port);
    qDebug() << "TCPHandler reconnectToHost()";

    this->incomingFrameLength = 0;
}

bool TCPHandler::tryToListen()
{
    if (tcpServer->isListening())
        tcpServer->close();

    return true;
}

void TCPHandler::startListening()
{
    while (!tryToListen()) {
        if (QMessageBox::question(new QWidget(), tr("Start the server"), tr("Could not start the server. Try again?"), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Ok)
            break;
    }
}
