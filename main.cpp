#include "playerwidget.h"
#include "devicescreenwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerWidget w;
    //DeviceScreenWidget w;
    w.show();

    return a.exec();
}
