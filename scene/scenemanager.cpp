/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#include "scene/scenemanager.h"

#include <QWidget>

SceneManager::SceneManager(Isometric *isometric)
{
    this->m_defaultScene = new Scene(isometric);
}

SceneManager::~SceneManager() {}


void SceneManager::CreateScene() {}

Scene *SceneManager::GetScene(const QString &sceneName)
{
    Q_UNUSED(sceneName)

    return this->m_defaultScene;
}

void SceneManager::paintEvent(const QPaintEvent *event)
{
    Q_UNUSED(event);
}

void SceneManager::resizeEvent(const QResizeEvent *event)
{
    Q_UNUSED(event);
}

void SceneManager::mousePressEvent(const QMouseEvent *event)
{
    this->m_defaultScene->mousePressEvent(event);
}


void SceneManager::mouseReleaseEvent(const QMouseEvent *event)
{
    Q_UNUSED(event);
}


void SceneManager::mouseMoveEvent(const QMouseEvent *event)
{
    this->point = event->pos();
}

