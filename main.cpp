#include "playerwidget.h"
#include "devicescreenportrait.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerWidget w;
    //DeviceScreenPortrait w;
    w.show();

    return a.exec();
}
