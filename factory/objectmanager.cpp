/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "factory/objectmanager.h"
#include "camera/maincamera.h"

#include <QDebug>
#include <QImage>
#include <QImageReader>
#include <QObject>
#include <QPainter>
#include <QPixmap>

#define DEUBG

/*!
 * \brief ObjectCreator::ObjectCreator
 */
ObjectManager::ObjectManager(Isometric *isometric)
{
    this->m_isometric = isometric;
}

ObjectManager::~ObjectManager()
{
    this->m_objectList.clear();
}

void ObjectManager::Create(int categoly)
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


void ObjectManager::CreateCharactor()
{
    // 오브젝트 생성
    OwObject *owObject = new OwObject(this->m_isometric);
    owObject->setParent(this);
    //*owObject->m_splitObjectInfo = new ObjectSplitImageInfo[2];

    // 남쪽방향 이동
    ObjectSplitImageInfo *moveS = new ObjectSplitImageInfo();
    moveS->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveS->copyStartPoint = QPoint(0, 0);
    moveS->copyDirection = IOwObject::COPY_RIGHT;
    moveS->fullWidth = 96;
    moveS->fullHeight = 32;
    moveS->width = 32;
    moveS->height = 32;
    moveS->actionNo = IOwObject::DIRECTION_S;
    moveS->totalSplitCount = 3;
    moveS->movePixel = 2;
    owObject->m_splitObjectInfo.insert(IOwObject::DIRECTION_S, moveS);

    // 북쪽방향 이동
    ObjectSplitImageInfo *moveN = new ObjectSplitImageInfo();
    moveN->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveN->copyDirection = IOwObject::COPY_RIGHT;
    moveN->copyStartPoint = QPoint(0, 98);
    moveN->fullWidth = 96;
    moveN->fullHeight = 32;
    moveN->width = 32;
    moveN->height = 32;
    moveN->actionNo = IOwObject::DIRECTION_N;
    moveN->totalSplitCount = 3;
    moveN->movePixel = 2;
    owObject->m_splitObjectInfo.insert(IOwObject::DIRECTION_N, moveN);

    // 오브젝트 등록
    owObject->SetObjectSplitImageInfo(owObject->m_splitObjectInfo);
    this->m_objectList.insert(IOwObject::STATUS_WORK, owObject);
}

void ObjectManager::CreateObject() {}

void ObjectManager::DrawObjects(QPainter *painter)
{
    if (this->m_objectList.size() <= 0)
        return;

    if (this->m_objectList[IOwObject::STATUS_WORK]) {
        this->m_objectList[IOwObject::STATUS_WORK]->DrawObject(painter);
    }
}

void ObjectManager::MouseDown(int metricX, int metricY)
{
    this->m_objectList[IOwObject::STATUS_WORK]->MouseDown(metricX, metricY);
}

void ObjectManager::MouseUp(int metricX, int metricY)
{
    Q_UNUSED(metricX)
    Q_UNUSED(metricY)
}

void ObjectManager::MouseMove(int metricX, int metricY)
{
    Q_UNUSED(metricX)
    Q_UNUSED(metricY)
}
