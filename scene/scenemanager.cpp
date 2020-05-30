/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#include "scenemanager.h"

#include <QWidget>

#include <openworldwidget/owdrawwidget.h>


SceneManager::SceneManager(Isometric *isometric)
{
    this->m_defaultScene = new Scene();
    this->m_defaultScene->SetIsometric(isometric);
    connect(&timer, SIGNAL (timeout()), this, SLOT (SceneWork()));
}

SceneManager::~SceneManager() {}


void SceneManager::CreateScene() {}

Scene *SceneManager::GetScene(QString &sceneName)
{
    return this->m_defaultScene;
}

void SceneManager::SetCamera(const MainCamera &camera)
{
    //this->m_mainCamera = camera;
}

void SceneManager::SceneAction()
{
    timer.start(18);
}

void SceneManager::SceneStop()
{
    timer.stop();
}

void SceneManager::SceneWork()
{
    // 주기적 업데이트는 필요 없어 보인다.
    // 케릭터가 움직일 경우에만 쓰레드 처리하면 될 것 같다.
    // sample
    //((OWDrawWidget *) this->parent())- >FadeIn();
    //> update();
    //this->m_mainCamera.Draw()
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
    qDebug() << "마우스 클릭함";
    qDebug() << "Mouse Location : " << QString::number(event->x()) << ", "
             << QString::number(event->y());
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

