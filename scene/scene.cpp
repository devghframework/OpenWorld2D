#include "scene/scene.h"

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QtGlobal>

//#define DEBUG


Scene::Scene()
{
    connect(&timer, SIGNAL (timeout()), this, SLOT (SceneWork()));
    //timer.start(18);
}

Scene::~Scene()
{
    timer.stop();
}

void Scene::SceneWork()
{

}
