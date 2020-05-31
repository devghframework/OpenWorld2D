/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QMouseEvent>

#include <tilemap/tilemap.h>

#include <factory/objectmanager.h>
#include <factory/owobject.h>
#include <coordinatesystem/isometric.h>


/*!
 * \class Scene
 * \brief The Scene class
 *
 * 배경과 인물/사물등을 구성하는 클래스
 */
class Scene : public QObject
{
    Q_OBJECT

public:
    Scene();
    virtual ~Scene();

    void SetIsometric(Isometric *);

    void mousePressEvent(const QMouseEvent *);
    void mouseReleaseEvent(const QMouseEvent *);
    void mouseMoveEvent(const QMouseEvent *);

private:
    TileMap *m_tileMap; // 씬의 배경 그림 (이미지가 아니라 데이타 형태로 불러와야 함)
    ObjectManager *m_objectManager; // 등장인물과 사물들 생성 관리자.
    Isometric *m_isoMetric;
};

#endif // SCENE_H
