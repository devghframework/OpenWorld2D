/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "factory/owobject.h"

#include <QPainter>


OwObject::OwObject()
    :IOwObject()
{

}

QMap<QString, QObject> OwObject::GetObjects()
{
    QMap<QString, QObject> empty;
    return empty;
}


QObject *OwObject::GetObject(QString key)
{
    QObject *obj = new QObject();
    return obj;
}


void OwObject::CreateObject()
{

}


void OwObject::DrawObject(QPainter *painter)
{
    painter->drawPixmap(100, 100, this->m_splitObjectInfo->splitImage[0]);
}


void OwObject::MouseDown(int metricX, int metricY)
{

}


void OwObject::MouseUp(int metricX, int metricY)
{

}


void OwObject::MouseMove(int metricX, int metricY)
{

}

void OwObject::SetObjectSplitImageInfo(ObjectSplitImageInfo *objInfo)
{
    this->m_splitObjectInfo = objInfo;
    // TODO : 아래 함수 구현해야 함.
    // InitObjectDataMap();
}


ObjectSplitImageInfo *OwObject::GetObjectSplitImageInfo()
{
    return this->m_splitObjectInfo;
}
