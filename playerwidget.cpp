#include "playerwidget.h"
#include "ui_playerwidget.h"

#include <QDebug>
#include "udphandler.h"
#include "tcphandler.h"


PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    //connectionHandler = new UDPHandler(this);
    connectionHandler = new TCPHandler(this);
    //screenWidget = new DeviceScreenWidget(this);

    logFile.setFileName("log.txt");
    if (!logFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Could not create log file...";
        isLogging = false;
    }
    else {
        logStream.setDevice(&logFile);
        isLogging = true;
    }

    fps = 0;

    connect(connectionHandler, &ConnectionHandler::newFrame, &screenWidget, &DeviceScreenWidget::handleImage);
    connect(connectionHandler, &ConnectionHandler::newParametersRect, &screenWidget, &DeviceScreenWidget::updateRectCoord);
    connect(&screenWidget, SIGNAL(reconnect()), connectionHandler, SLOT(reconnectToHost()));

    this->close();
    screenWidget.show();
    //screenWidget.activateWindow();

}

PlayerWidget::~PlayerWidget()
{
    logFile.close();

    //screenWidget->deleteLater();
    delete ui;
}

void PlayerWidget::printFrameRate()
{
    if (isLogging)
        logStream << QString("%1 fps\n").arg(fps);
    fps = 0;
}
