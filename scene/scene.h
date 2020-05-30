#ifndef SCENE_H
#define SCENE_H

#include <QObject>

#include <tilemap/tilemap.h>

#include <factory/objectmanager.h>
#include <factory/owobject.h>

/*!
 * \class Scene
 * \brief The Scene class
 *
 * 배경과 인물등을 구성하는 클래스
 */
class Scene : public QObject
{
    Q_OBJECT

public:
    Scene();
    virtual ~Scene();


private:
    TileMap *m_tileMap;
    ObjectManager *m_objectCreator;

};

#endif // SCENE_H
