#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "devicescreenwidget.h"
#include "connectionhandler.h"

namespace Ui {
class PlayerWidget;
}

class QUdpSocket;

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();

private slots:

    void printFrameRate();

signals:


private:
    Ui::PlayerWidget *ui;
    DeviceScreenWidget screenWidget;
    ConnectionHandler *connectionHandler;

    QTimer timer;
    int fps;

    QFile logFile;
    QTextStream logStream;
    bool isLogging;


};

#endif // PLAYERWIDGET_H
