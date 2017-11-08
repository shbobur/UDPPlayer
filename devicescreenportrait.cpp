#include "devicescreenportrait.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

DeviceScreenPortrait::DeviceScreenPortrait(QWidget *parent) :
    DeviceScreen(parent)
{

    // layout for 3 buttons on the surface
    QHBoxLayout *lytSurfaceBtns = new QHBoxLayout;
    lytSurfaceBtns->addWidget(this->btnOverview);
    lytSurfaceBtns->addWidget(this->btnHome);
    lytSurfaceBtns->addWidget(this->btnBack);

    // layout for buttons on the sides
    QHBoxLayout *lytSideBtns = new QHBoxLayout;
    lytSideBtns->addWidget(this->btnVolUp);
    lytSideBtns->addWidget(this->btnVolDown);
    lytSideBtns->addWidget(this->btnPower);
    //QSpacerItem *spacer = new QSpacerItem;
    //lytSideBtns->addSpacerItem(spacer);
    lytSideBtns->addWidget(this->lblFrameRateText);
    lytSideBtns->addWidget(this->lblFrameRate);


    // set Graphics View size
    playerGraphicsView->setFixedWidth(ShortSide);
    playerGraphicsView->setFixedHeight(LongSide);
    playerGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerGraphicsView->setSceneRect(0, 0, ShortSide, LongSide);

    QVBoxLayout *lytMain = new QVBoxLayout(this);
    lytMain->setMargin(0);
    lytMain->setSpacing(2);
    lytMain->addLayout(lytSideBtns);
    lytMain->addWidget(this->playerGraphicsView);
    lytMain->addLayout(lytSurfaceBtns);

    this->setLayout(lytMain);
}

DeviceScreenPortrait::~DeviceScreenPortrait()
{

}
