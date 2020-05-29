#ifndef SCENE_H
#define SCENE_H

#include <QObject>

#include <tilemap/tilemap.h>

#include <factory/objectcreator.h>
#include <factory/owobject.h>

class Scene : public QObject
{
    Q_OBJECT

public:
    Scene();
    virtual ~Scene();


private slots:
    void SceneWork();

private:
    QTimer timer;

private:
    /*!
     * \brief mainThread
     */
    QThread *m_mainThread;

    TileMap *m_tileMap;
    ObjectCreator *m_objectCreator;
};

#endif // SCENE_H
