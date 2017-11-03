#ifndef DEVICESCREENWIDGET_H
#define DEVICESCREENWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "devicescreenportrait.h"

enum ScreenOrientation { Portrait = 0, Landscape};

namespace Ui {
class DeviceScreenWidget;
}

class QGraphicsScene;
class QGraphicsPixmapItem;

class DeviceScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceScreenWidget(QWidget *parent = 0);
    ~DeviceScreenWidget();

    void handleImage(QPixmap pixmap);

private slots:
    void showMouseCoord(QString);
    void on_pushButton_clicked();
    void on_adbStartAppButton_clicked();

signals:
    void reconnect();

private:
    void startMobileApp();
    void stopMobileApp();
    void forwardAdbPort();

    Ui::DeviceScreenWidget *ui;

    QVBoxLayout *lytPortrait;
    QHBoxLayout *lytLandscape;
    DeviceScreenPortrait *screenPortrait;

    //GraphicsScene *scene;
    bool receivingImage;

    QGraphicsPixmapItem *imageItem;
    ScreenOrientation sOrientaion;
    int longSide, shortSide;
    quint32 width, height;
};

#endif // DEVICESCREENWIDGET_H
