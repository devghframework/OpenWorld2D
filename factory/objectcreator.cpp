/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "objectcreator.h"

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

    QString fileName = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    QImageReader r(fileName);
    r.setDecideFormatFromContent(true);
    QImage i = r.read();
    if (!i.isNull()) {

        QPixmap pixmap;
        pixmap = QPixmap::fromImage(i);

        objInfo->width = 32;
        objInfo->height = 32;
        objInfo->fullWidth = 96;
        objInfo->fullHeight = 32;
        objInfo->actionNo = 1;
        objInfo->totalCount = 3;

        objInfo->splitImage = new QPixmap[objInfo->totalCount];
        objInfo->splitImage[0] = pixmap.copy(0, 0, objInfo->width, objInfo->height);
        objInfo->splitImage[1] = pixmap.copy(32, 0, objInfo->width, objInfo->height);
        objInfo->splitImage[2] = pixmap.copy(64, 0, objInfo->width, objInfo->height);

        charector.SetObjectSplitImageInfo(objInfo);

        this->m_objectList.insert("1", charector);
    }
    else {
#ifdef DEBUG
    qDebug("마우스 포인터 이미지를 읽을 수 없습니다.");
    //libpng warning: iCCP: CRC error : 이미지 포멧이 잘못 되었을 경우
#endif
    }
}


void ObjectCreator::CreateObject()
{

}


OwObject ObjectCreator::GetObject(QString key)
{
    OwObject object =this->m_objectList[key];
}


void ObjectCreator::DrawObjects(QPainter *painter)
{
    if(this->m_objectList.size()<=0) return;

    for(int i=0; i<this->m_objectList.size(); i++) {
        OwObject obj = this->m_objectList["1"];
        ObjectSplitImageInfo *charector = obj.GetObjectSplitImageInfo();
        painter->drawPixmap(100, 100, charector->splitImage[0]);
    }
}
