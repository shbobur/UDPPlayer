#ifndef DEVICESCREENLANDSCAPE_H
#define DEVICESCREENLANDSCAPE_H

#include "devicescreen.h"

class DeviceScreenLandscape : public DeviceScreen
{
    Q_OBJECT

public:
    DeviceScreenLandscape(QWidget *parent = 0);
    ~DeviceScreenLandscape();
};

#endif // DEVICESCREENLANDSCAPE_H
