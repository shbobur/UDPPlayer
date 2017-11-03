#include "devicescreen.h"

DeviceScreen::DeviceScreen(QWidget *parent) : QWidget(parent)
{
    // screen of mobile device
    playerGraphicsView = new QGraphicsView(this);
    playerScene = new GraphicsScene(this);
    playerGraphicsView->setScene(playerScene);

    // control buttons
    // on the surface (home, back, Overview (app chooser))
    btnHome = new QPushButton(tr("Home"), this);
    btnBack = new QPushButton(tr("Back"), this);
    btnOverview = new QPushButton(tr("Recent"), this);

    // on the sides (Power on/off, Volume up/down)
    btnPower = new QPushButton(tr("On/Off"), this);
    btnVolUp = new QPushButton(tr("Vol+"), this);
    btnVolDown = new QPushButton(tr("Vol-"), this);

}

DeviceScreen::~DeviceScreen()
{
    // screen of mobile device
    delete playerGraphicsView;
    delete playerScene;

    // control buttons
    // on the surface (home, back, Overview (app chooser))
    delete btnHome;
    delete btnBack;
    delete btnOverview;

    // on the sides (Power on/off, Volume up/down)
    delete btnPower;
    delete btnVolUp;
    delete btnVolDown;
}

quint32 DeviceScreen::getWidth() const
{
    return width;
}

void DeviceScreen::setWidth(const quint32 &value)
{
    width = value;
}

quint32 DeviceScreen::getHeight() const
{
    return height;
}

void DeviceScreen::setHeight(const quint32 &value)
{
    height = value;
}

void DeviceScreen::updateImage(QPixmap pixmap)
{
    playerScene->clear();
    playerScene->addPixmap(pixmap);//.scaled(width, height, Qt::KeepAspectRatio));
}
