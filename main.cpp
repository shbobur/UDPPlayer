#include "playerwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerWidget w;
    w.show();

    return a.exec();
}
