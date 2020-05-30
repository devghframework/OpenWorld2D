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
class ObjectManager
{

public:
    ObjectManager();
    virtual ~ObjectManager();

    void Create(int categoly);
    OwObject GetObject(QString key);
    void DrawObjects(QPainter *painter);


private:
    QMap<QString, OwObject> m_objectList;


private:
    void CreateCharactor();
    void CreateObject();
};

#endif // OBJECTCREATOR_H
