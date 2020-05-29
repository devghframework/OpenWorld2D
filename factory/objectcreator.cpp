/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "factory/objectcreator.h"

#include <QDebug>
#include <QPixmap>
#include <QImageReader>
#include <QImage>


#define DEUBG

/*!
 * \brief ObjectCreator::ObjectCreator
 */
ObjectCreator::ObjectCreator()
{

}

ObjectCreator::~ObjectCreator()
{
    this->m_objectList.clear();
}

void ObjectCreator::Create(int categoly)
{

    switch (categoly) {
    case 1:
        CreateCharactor();
        break;
    case 2:
        CreateObject();
        break;
    default:
        break;
    }
}


void ObjectCreator::CreateCharactor()
{
    OwObject charector;

    ObjectSplitImageInfo *objInfo = charector.GetObjectSplitImageInfo();
    objInfo = new ObjectSplitImageInfo();
    objInfo->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    objInfo->copyStartPoint = QPoint(0, 0);
    objInfo->fullWidth = 96;
    objInfo->fullHeight = 32;
    objInfo->width = 32;
    objInfo->height = 32;
    objInfo->actionNo = 1;
    objInfo->totalSplitCount = 3;

    charector.SetObjectSplitImageInfo(objInfo);

    this->m_objectList.insert("1", charector);
}


void ObjectCreator::CreateObject()
{

}


OwObject ObjectCreator::GetObject(QString key)
{
    OwObject object =this->m_objectList[key];
    return object;
}


void ObjectCreator::DrawObjects(QPainter *painter)
{
    if(this->m_objectList.size()<=0) return;

    for(int i=0; i<this->m_objectList.size(); i++) {
        OwObject obj = this->m_objectList["1"];
        ObjectSplitImageInfo *charector = obj.GetObjectSplitImageInfo();
        painter->drawPixmap(100, 100, charector->splitImage[0]);
        painter->drawPixmap(132, 100, charector->splitImage[1]);
        painter->drawPixmap(164, 100, charector->splitImage[2]);
    }
}
