#ifndef DEVICESCREEN_H
#define DEVICESCREEN_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include "graphicsscene.h"

enum {ShortSide = 360, LongSide = 640};

class DeviceScreen : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceScreen(QWidget *parent = nullptr);
    ~DeviceScreen();

    quint32 getWidth() const;
    void setWidth(const quint32 &value);

    quint32 getHeight() const;
    void setHeight(const quint32 &value);

    void updateImage(QPixmap pixmap);

signals:

public slots:

protected:
    // screen of mobile device
    QGraphicsView *playerGraphicsView;
    GraphicsScene *playerScene;

    // control buttons
    // on the surface (home, back, Overview (app chooser))
    QPushButton *btnHome;
    QPushButton *btnBack;
    QPushButton *btnOverview;

    // on the sides (Power on/off, Volume up/down)
    QPushButton *btnPower;
    QPushButton *btnVolUp;
    QPushButton *btnVolDown;

private:
    quint32 width, height;

};

#endif // DEVICESCREEN_H
