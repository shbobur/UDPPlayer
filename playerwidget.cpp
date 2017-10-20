#include "playerwidget.h"
#include "ui_playerwidget.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QPixmap>

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    client = new QUdpSocket;
    fps = 0;

    client->bind(ui->portLine->text().toInt());
    ui->logger->append(QString("Bound to port %1").arg(ui->portLine->text()));

    connect(client, &QIODevice::readyRead, this, &PlayerWidget::readBytes);
    connect(this, &PlayerWidget::newFrame, this, &PlayerWidget::handleImage);
    connect(&timer, &QTimer::timeout, this, &PlayerWidget::printFrameRate);

    timer.setInterval(1000);
    timer.start();
}

PlayerWidget::~PlayerWidget()
{
    if (client->isOpen())
        client->disconnect();
    client->deleteLater();
    delete ui;
}

void PlayerWidget::readBytes()
{
    QByteArray datagram;

    int size = client->pendingDatagramSize();
    do {
        //qDebug() << QString("Receiving %1 bytes").arg(client->pendingDatagramSize());
        datagram.resize(client->pendingDatagramSize());
        client->readDatagram(datagram.data(), datagram.size());
    } while (client->hasPendingDatagrams());

    //qDebug() << QString("Received %1").arg(datagram.size());

    //int size;
    //QDataStream in(&datagram, QIODevice::ReadOnly);
    //in.setVersion(QDataStream::Qt_5_9);

    //QByteArray imageByte;
    //in >> imageByte;
    //qDebug() << imageByte.size() << " bytes are read from stream";
    QImage image;
    //image.loadFromData(imageByte, "JPEG");
    image.loadFromData(datagram, "JPEG");
    if (!image.isNull()) {
        emit newFrame(image);
       // ui->logger->append(QString("Valid frame received: %1").arg(size));
    } else
        ui->logger->append("Cannot decode image");
}

void PlayerWidget::handleImage(QImage image)
{
    ui->player->setPixmap(QPixmap::fromImage(image));
    fps++;
}

void PlayerWidget::printFrameRate()
{
    ui->logger->append(QString("%1 frames/s").arg(fps));
    fps = 0;
}

void PlayerWidget::on_bindButton_clicked()
{
    //client->bind(ui->portLine->text().toInt());
}
