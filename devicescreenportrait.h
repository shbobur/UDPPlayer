#ifndef DEVICESCREENPORTRAIT_H
#define DEVICESCREENPORTRAIT_H

#include "devicescreen.h"

class DeviceScreenPortrait : public DeviceScreen
{
    Q_OBJECT
public:
    DeviceScreenPortrait(QWidget *parent = nullptr);
    ~DeviceScreenPortrait();
};

#endif // DEVICESCREENPORTRAIT_H
