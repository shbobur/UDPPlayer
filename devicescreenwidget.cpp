#include "devicescreenwidget.h"
#include "ui_devicescreenwidget.h"

#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPushButton>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QTime>

#define RECT_SIDE 30

DeviceScreenWidget::DeviceScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceScreenWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(onOrientationChanged()));

    screenPortrait = new DeviceScreenPortrait(this);
    screenLandscape = new DeviceScreenLandscape(this);

    screenLandscapeSizeHint = screenLandscape->minimumSizeHint();
    screenPortraitSizeHint = screenPortrait->minimumSizeHint();

    // portrait screen layout
    lytPortrait = new QVBoxLayout;
    lytPortrait->setMargin(0);
    lytPortrait->addWidget(screenPortrait);

    // landscape screen layout
    lytLandscape = new QHBoxLayout;
    lytLandscape->setMargin(0);
    lytLandscape->addWidget(screenLandscape);

    ui->page->setLayout(lytPortrait);
    ui->page_2->setLayout(lytLandscape);

    onOrientationChanged();

    this->activateWindow();

    forwardAdbPort();
    startMobileApp();

    rectX = 0;
    rectY = 0;
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
        screenLandscape->updateImage(pixmap);
        QBrush blueBrush(Qt::transparent);
        QPen outlinePen(Qt::white);
        outlinePen.setWidth(3);
        QGraphicsRectItem *rectangle = screenLandscape->playerScene->addRect(rectX, rectY, 50, 50, outlinePen, blueBrush);
        //screenLandscape->playerScene->addRect((qreal)x, (qreal)y, (qreal)RECT_SIDE, (qreal)RECT_SIDE);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {                                    // portrait
        sOrientaion = Portrait;
        screenPortrait->updateImage(pixmap);
        QBrush blueBrush(Qt::transparent);
        QPen outlinePen(Qt::white);
        outlinePen.setWidth(3);
        QGraphicsRectItem *rectangle = screenLandscape->playerScene->addRect(rectX, rectY, 50, 50, outlinePen, blueBrush);

        ui->stackedWidget->setCurrentIndex(0);
    }
}

void DeviceScreenWidget::onOrientationChanged()
{
    if (sOrientaion == Portrait) {
        ui->page->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->page_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        this->setFixedSize(screenPortrait->minimumSizeHint());
        ui->stackedWidget->adjustSize();
        this->adjustSize();
    }
    else if (sOrientaion == Landscape) {  // sOrientation = Landscape
        ui->page_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->page->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        this->setFixedSize(screenLandscape->minimumSizeHint());
        ui->stackedWidget->adjustSize();
        this->adjustSize();
    }
}

void DeviceScreenWidget::showMouseCoord(QString coord)
{
    //` ui->mouseCoordLabel->setText(coord);
}

void DeviceScreenWidget::updateRectCoord(qreal x, qreal y)
{
    this->rectX = x;
    this->rectY = y;
}

void DeviceScreenWidget::startMobileApp()
{
    QString cmd = "C:/Users/Bobur/AppData/Local/Android/sdk/platform-tools/adb.exe -s 0715f7cda8412c36 shell am start -n com.example.admin.streammediaprojection/com.example.admin.streammediaprojection.MainActivity";
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
    QString cmd = "C:/Users/Bobur/AppData/Local/Android/sdk/platform-tools/adb.exe -s 0715f7cda8412c36 shell pm clear com.example.admin.streammediaprojection";
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
