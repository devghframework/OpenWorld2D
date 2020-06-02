/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include "factory/owobject.h"

#include <QMap>
#include <QObject>

#include <coordinatesystem/isometric.h>

//#include <helper/utils.h>

/*!
 * \class ObjectCreator
 * \brief The ObjectCreator class
 *
 * 팩터리 패턴과 데코레이터 패턴으로 객체 생성시 행동 양식을 주입해 생성한다.
 *
 * [오브젝트 카테고리]
 * TODO : 케릭터/사물 추후정리 ...
 ************************************
 * 임시카테고리
 ************************************
 * 카테고리 번호      설명
 * ----------------------------------
 * 1               케릭터
 * 1-1             주인공
 ************************************
 */
class OwObjectManager : public QObject
{
    Q_OBJECT

public:
    OwObjectManager(Isometric *);
    virtual ~OwObjectManager();

    void Create(int categoly);
    OwObject *GetObject(int);
    int GetObjectsCount();
    void DrawObjects(QPainter *painter);

    // 움직일 수 있는 오브젝트에게만 이벤트를 전달한다.
    // 현재는 카테고리 1 (케릭터) 만 존재한다.
    void MouseDown(int metricX, int metricY);
    void MouseUp(int metricX, int metricY);
    void MouseMove(int metricX, int metricY);

private:
    Isometric *m_isometric;
    QMap<int, OwObject *> m_objectList;
    //static Utils *m_util;

private:
    void CreateCharactor();
    void CreateObject();
};

#endif // OBJECTCREATOR_H
