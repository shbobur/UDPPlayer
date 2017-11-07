#include "devicescreenlandscape.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

DeviceScreenLandscape::DeviceScreenLandscape(QWidget *parent) :
    DeviceScreen(parent)
{

    // resize surface buttons
    int width = this->btnVolDown->height();
    int height = ShortSide / 3 - 2;
    this->btnHome->setMaximumWidth(width);
    this->btnHome->setMinimumHeight(height);
    this->btnOverview->setMaximumWidth(width);
    this->btnOverview->setMinimumHeight(height);
    this->btnBack->setMaximumWidth(width);
    this->btnBack->setMinimumHeight(height);

    // layout for 3 buttons on the surface
    QVBoxLayout *lytSurfaceBtns = new QVBoxLayout;
    lytSurfaceBtns->addWidget(this->btnOverview);
    lytSurfaceBtns->addWidget(this->btnHome);
    lytSurfaceBtns->addWidget(this->btnBack);

    // layout for buttons on the sides
    QHBoxLayout *lytSideBtns = new QHBoxLayout;
    lytSideBtns->addWidget(this->btnVolUp);
    lytSideBtns->addWidget(this->btnVolDown);
    lytSideBtns->addWidget(this->btnPower);

    // set Graphics View size
    playerGraphicsView->setFixedWidth(LongSide);
    playerGraphicsView->setFixedHeight(ShortSide);
    playerGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerGraphicsView->setSceneRect(0, 0, LongSide, ShortSide);

    // layout for GraphicsView and buttons on the surface
    QHBoxLayout *lytSurface = new QHBoxLayout;
    lytSurface->addWidget(this->playerGraphicsView);
    lytSurface->addLayout(lytSurfaceBtns);

    QVBoxLayout *lytMain = new QVBoxLayout(this);
    lytMain->setMargin(0);
    lytMain->setSpacing(2);
    lytMain->addLayout(lytSideBtns);
    lytMain->addLayout(lytSurface);

    this->setLayout(lytMain);
}

DeviceScreenLandscape::~DeviceScreenLandscape()
{

}
