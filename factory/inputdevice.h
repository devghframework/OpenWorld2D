/*!
    Copyright 2020. Coding Studio. All rights reserved.
    BSD License Usage
    
    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

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
