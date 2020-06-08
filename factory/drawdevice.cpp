/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#include "factory/drawdevice.h"
#include "factory/iowobject.h"
#include "factory/owobject.h"

DrawDevice::DrawDevice() {}

DrawDevice::~DrawDevice() {}

void DrawDevice::Update(QObject *qobject, QPainter &painter)
{
    OwObject *object = qobject_cast<OwObject *>(qobject);

    if (object->GetObjectStatus() == IOwObject::STATUS_NONE) {
        object->InitAnimation();
    }

    if (object->GetSplitObjectInfoCount() > 0) {
        painter.drawPixmap(object->GetMovePointPixel().x()
                               + object->GetSplitObjectInfo(object->GetActionName())
                                     ->bottomGapFromMetricCenter.x(),
                           object->GetMovePointPixel().y()
                               + object->GetSplitObjectInfo(object->GetActionName())
                                     ->bottomGapFromMetricCenter.y(),
                           object->GetSplitObjectInfo(object->GetActionName())
                               ->splitImage[object->GetAnimationNo()]);

        object->AddAnimationNo();

        if (object->GetAnimationNo()
            >= object->GetSplitObjectInfo(object->GetActionName())->totalSplitCount) {
            object->InitAnimation();
        }
    }
}
