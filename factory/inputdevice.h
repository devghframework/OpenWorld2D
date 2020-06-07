#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "coordinatesystem/isometric.h"

#include <QObject>

class InputDevice
{
public:
    InputDevice();
    virtual ~InputDevice();

    void Update(QObject *, Isometric &);
};

#endif // INPUTDEVICE_H
