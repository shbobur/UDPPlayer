#include "devicescreenwidget.h"
#include "ui_devicescreenwidget.h"

#include <QGraphicsPixmapItem>
#include <QImage>
#include <QGraphicsScene>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QVBoxLayout>
#include <QTime>

DeviceScreenWidget::DeviceScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceScreenWidget)
{
    ui->setupUi(this);

    sOrientaion = Portrait;
    shortSide = 360; // 480;
    longSide = 640; //853;
    width = shortSide;
    height = longSide;

    scene = new GraphicsScene(this);
    connect(scene, SIGNAL(mouseCoordinates(QString)), this, SLOT(showMouseCoord(QString)));

    QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":/SVkVXu-T_400x400_JPEG.jpg")));
    scene->addItem(imageItem);
    ui->playerGraphicsView->setScene(scene);
    ui->playerGraphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->playerGraphicsView->setFixedSize(width+2, height+2);
    ui->playerGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->playerGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->playerGraphicsView->setFixedSize(width+2*ui->playerGraphicsView->frameWidth(), height+2*ui->playerGraphicsView->frameWidth());
    ui->playerGraphicsView->setSceneRect(0, 0, width, height);
    //ui->playerGraphicsView->setSceneRect(0, 0, width, height);
   // ui->playerGraphicsView->fitInView(0, 0, width, height, Qt::KeepAspectRatio);
    forwardAdbPort();
    startMobileApp();
}

DeviceScreenWidget::~DeviceScreenWidget()
{
    delete ui;
    stopMobileApp();
}

void DeviceScreenWidget::handleImage(QPixmap pixmap)
{
    //QPixmap pixmap;
    if (pixmap.width() > pixmap.height()) {   // if landscape mode
        sOrientaion = Landscape;
        width = longSide;
        height = shortSide;
    }
    else {                                    // portrait
        sOrientaion = Portrait;
        width = shortSide;
        height = longSide;
    }

    scene->clear();
    scene->addPixmap(pixmap.scaled(width, height, Qt::KeepAspectRatio));
    //scene->addItem(new QGraphicsPixmapItem(pixmap.scaled(width, height)));

    //qDebug() << "Tried to display image..." << QTime::currentTime().toString();
}

void DeviceScreenWidget::showMouseCoord(QString coord)
{
    ui->mouseCoordLabel->setText(coord);
}

void DeviceScreenWidget::on_pushButton_clicked()
{
    emit reconnect();
}

void DeviceScreenWidget::on_adbStartAppButton_clicked()
{
    startMobileApp();
}

void DeviceScreenWidget::startMobileApp()
{
    QString cmd = "C:/Users/Bobur/AppData/Local/Android/sdk/platform-tools/adb.exe shell am start -n com.example.admin.streammediaprojection/com.example.admin.streammediaprojection.MainActivity";
    QProcess *p = new QProcess(this);
    p->start(cmd);
    p->waitForFinished(-1);
    qDebug()<<QString("QProcess finished with exit code: %1 %2")
              .arg(p->exitCode())
              .arg(p->errorString());
    QString result = p->readAllStandardOutput();
    qDebug() << result;
}

void DeviceScreenWidget::stopMobileApp()
{
    QString cmd = "C:/Users/Bobur/AppData/Local/Android/sdk/platform-tools/adb.exe -s 02157df27a5a001e shell pm clear com.example.admin.streammediaprojection";
    QProcess *p = new QProcess(this);
    p->start(cmd);
    p->waitForFinished(-1);
    qDebug()<<QString("QProcess finished with exit code: %1 %2")
              .arg(p->exitCode())
              .arg(p->errorString());
    QString result = p->readAllStandardOutput();
    qDebug() << result;
}

void DeviceScreenWidget::forwardAdbPort()
{
    QString cmd = "C:/Users/Bobur/AppData/Local/Android/sdk/platform-tools/adb.exe forward tcp:5900 tcp:6600";
    QProcess *p = new QProcess(this);
    p->start(cmd);
    p->waitForFinished(-1);
    qDebug()<<QString("QProcess finished with exit code: %1 %2")
              .arg(p->exitCode())
              .arg(p->errorString());
    QString result = p->readAllStandardOutput();
    qDebug() << result;
}
