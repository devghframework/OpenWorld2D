/*!
    Copyright 2020. Coding Studio. All rights reserved.
    BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include <QObject>
#include <QPainter>

class DrawDevice
{
public:
    DrawDevice();
    virtual ~DrawDevice();

    void Update(QObject *, QPainter &);
};

#endif // DRAWDEVICE_H
