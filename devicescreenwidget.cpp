#include "devicescreenwidget.h"
#include "ui_devicescreenwidget.h"

#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPushButton>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QTime>

DeviceScreenWidget::DeviceScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceScreenWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(onOrientationChanged()));

    screenPortrait = new DeviceScreenPortrait(this);
    screenLandscape = new DeviceScreenLandscape(this);

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
    this->resize(this->minimumSizeHint());

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
        screenLandscape->updateImage(pixmap);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {                                    // portrait
        sOrientaion = Portrait;
        screenPortrait->updateImage(pixmap);
        ui->stackedWidget->setCurrentIndex(0);
    }


   // scene->clear();
   // scene->addPixmap(pixmap.scaled(width, height, Qt::KeepAspectRatio));
    //scene->addItem(new QGraphicsPixmapItem(pixmap.scaled(width, height)));

    //qDebug() << "Tried to display image..." << QTime::currentTime().toString();
}

void DeviceScreenWidget::onOrientationChanged()
{

    /*QWidget* pPage = nullptr;
    QSizePolicy::Policy policy;// = QSizePolicy::Ignored;
    if (sOrientaion == Portrait) {
        pPage = ui->page;
        // update the size policy
        pPage->setSizePolicy (policy, policy);
        policy = QSizePolicy::Ignored;
        pPage->resize(ui->page->minimumSize());
    }
    else {  // sOrientation = Landscape
        pPage = ui->page_2;
        policy = QSizePolicy::Expanding;
        // update the size policy
        pPage->setSizePolicy (policy, policy);
        pPage->resize(ui->page->minimumSize());
    }
*/
}

void DeviceScreenWidget::showMouseCoord(QString coord)
{
   //` ui->mouseCoordLabel->setText(coord);
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
