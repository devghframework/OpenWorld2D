/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "factory/owobjectmanager.h"
#include "camera/maincamera.h"
//#include "helper/utils.h"

#include <QDebug>
#include <QImage>
#include <QImageReader>
#include <QMetaEnum>
#include <QObject>
#include <QPainter>
#include <QPixmap>

/*!
 * \brief ObjectCreator::ObjectCreator
 */
OwObjectManager::OwObjectManager(Isometric *isometric)
{
    //this->m_util = Utils::GetInstance();
    this->m_isometric = isometric;
}

OwObjectManager::~OwObjectManager()
{
    this->m_objectList.clear();
}

void OwObjectManager::Create(int categoly)
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

void OwObjectManager::CreateCharactor()
{
    // 오브젝트 생성
    OwObject *owObject = new OwObject(this->m_isometric);
    owObject->setParent(this);

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
    moveS->bottom.setX(16);
    moveS->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_S),
                                       moveS);

    // 북쪽방향 이동
    ObjectSplitImageInfo *moveN = new ObjectSplitImageInfo();
    moveN->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveN->copyDirection = IOwObject::COPY_RIGHT;
    moveN->copyStartPoint = QPoint(0, 96);
    moveN->fullWidth = 96;
    moveN->fullHeight = 32;
    moveN->width = 32;
    moveN->height = 32;
    moveN->actionNo = IOwObject::DIRECTION_N;
    moveN->totalSplitCount = 3;
    moveN->movePixel = 2;
    moveN->bottom.setX(16);
    moveN->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_N),
                                       moveN);

    ObjectSplitImageInfo *moveW = new ObjectSplitImageInfo();
    moveW->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveW->copyDirection = IOwObject::COPY_RIGHT;
    moveW->copyStartPoint = QPoint(0, 32);
    moveW->fullWidth = 96;
    moveW->fullHeight = 32;
    moveW->width = 32;
    moveW->height = 32;
    moveW->actionNo = IOwObject::DIRECTION_W;
    moveW->totalSplitCount = 3;
    moveW->movePixel = 2;
    moveW->bottom.setX(16);
    moveW->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_W),
                                       moveW);

    ObjectSplitImageInfo *moveE = new ObjectSplitImageInfo();
    moveE->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveE->copyDirection = IOwObject::COPY_RIGHT;
    moveE->copyStartPoint = QPoint(0, 64);
    moveE->fullWidth = 96;
    moveE->fullHeight = 32;
    moveE->width = 32;
    moveE->height = 32;
    moveE->actionNo = IOwObject::DIRECTION_E;
    moveE->totalSplitCount = 3;
    moveE->movePixel = 2;
    moveE->bottom.setX(16);
    moveE->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_E),
                                       moveE);

    ObjectSplitImageInfo *moveNE = new ObjectSplitImageInfo();
    moveNE->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveNE->copyDirection = IOwObject::COPY_RIGHT;
    moveNE->copyStartPoint = QPoint(96, 96);
    moveNE->fullWidth = 96;
    moveNE->fullHeight = 32;
    moveNE->width = 32;
    moveNE->height = 32;
    moveNE->actionNo = IOwObject::DIRECTION_NE;
    moveNE->totalSplitCount = 3;
    moveNE->movePixel = 2;
    moveNE->bottom.setX(16);
    moveNE->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_NE),
                                       moveNE);

    ObjectSplitImageInfo *moveNW = new ObjectSplitImageInfo();
    moveNW->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveNW->copyDirection = IOwObject::COPY_RIGHT;
    moveNW->copyStartPoint = QPoint(96, 32);
    moveNW->fullWidth = 96;
    moveNW->fullHeight = 32;
    moveNW->width = 32;
    moveNW->height = 32;
    moveNW->actionNo = IOwObject::DIRECTION_NW;
    moveNW->totalSplitCount = 3;
    moveNW->movePixel = 2;
    moveNW->bottom.setX(16);
    moveNW->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_NW),
                                       moveNW);

    ObjectSplitImageInfo *moveSE = new ObjectSplitImageInfo();
    moveSE->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveSE->copyDirection = IOwObject::COPY_RIGHT;
    moveSE->copyStartPoint = QPoint(96, 64);
    moveSE->fullWidth = 96;
    moveSE->fullHeight = 32;
    moveSE->width = 32;
    moveSE->height = 32;
    moveSE->actionNo = IOwObject::DIRECTION_SE;
    moveSE->totalSplitCount = 3;
    moveSE->movePixel = 2;
    moveSE->bottom.setX(16);
    moveSE->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_SE),
                                       moveSE);

    ObjectSplitImageInfo *moveSW = new ObjectSplitImageInfo();
    moveSW->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveSW->copyDirection = IOwObject::COPY_RIGHT;
    moveSW->copyStartPoint = QPoint(96, 0);
    moveSW->fullWidth = 96;
    moveSW->fullHeight = 32;
    moveSW->width = 32;
    moveSW->height = 32;
    moveSW->actionNo = IOwObject::DIRECTION_SW;
    moveSW->totalSplitCount = 3;
    moveSW->movePixel = 2;
    moveSW->bottom.setX(16);
    moveSW->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_MOVE_DIRECTION::DIRECTION_SW),
                                       moveSW);

    ObjectSplitImageInfo *moveArrived = new ObjectSplitImageInfo();
    moveArrived->originFileName
        = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/playerfull.png";
    moveArrived->copyDirection = IOwObject::COPY_RIGHT;
    moveArrived->copyStartPoint = QPoint(192, 128);
    moveArrived->fullWidth = 96;
    moveArrived->fullHeight = 32;
    moveArrived->width = 32;
    moveArrived->height = 32;
    moveArrived->actionNo = IOwObject::STATUS_ARRIVED;
    moveArrived->totalSplitCount = 3;
    moveArrived->movePixel = 2;
    moveArrived->bottom.setX(16);
    moveArrived->bottom.setX(32);
    owObject->m_splitObjectInfo.insert(IOwObject::GetMetaEnum(
                                           IOwObject::OBJECT_STATUS::STATUS_ARRIVED),
                                       moveArrived);

    // 오브젝트 등록
    owObject->SetObjectSplitImageInfo(owObject->m_splitObjectInfo);
    this->m_objectList.insert(IOwObject::STATUS_WORK, owObject);
}

void OwObjectManager::CreateObject() {}

void OwObjectManager::DrawObjects(QPainter *painter)
{
    if (this->m_objectList.size() <= 0)
        return;

    if (this->m_objectList[IOwObject::STATUS_WORK]) {
        this->m_objectList[IOwObject::STATUS_WORK]->DrawObject(painter);
    }
}

void OwObjectManager::MouseDown(int metricX, int metricY)
{
    this->m_objectList[IOwObject::STATUS_WORK]->MouseDown(metricX, metricY);
}

void OwObjectManager::MouseUp(int metricX, int metricY)
{
    Q_UNUSED(metricX)
    Q_UNUSED(metricY)
}

void OwObjectManager::MouseMove(int metricX, int metricY)
{
    Q_UNUSED(metricX)
    Q_UNUSED(metricY)
}
