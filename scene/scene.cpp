/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#include "scene/scene.h"

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QtGlobal>
#include <QPoint>


#include <isometric/isometric.h>


Scene::Scene()
{
    this->m_objectCreator = new ObjectManager();

    // 씬들은 에디터에 의해 생성되고 바이너리 파일로 저장되어 있어야 한다. --> 데이타 암호화 시켜야 한다.(네트워크 통신 프로토콜도 암호화 필요)
    // 현재 데이타 처리가 되어 있지 않아서 동적으로 임시로 생성한다.
    this->m_objectCreator->Create(1);  // 카테고리에 등록되어 있는 케릭터 생성
}

Scene::~Scene() {}

void Scene::SetIsometric(Isometric *isometric)
{
    this->m_isoMetric = isometric;
}


void Scene::mousePressEvent(const QMouseEvent *event)
{
    this->m_isoMetric->SetLocation(event->x(), event->y());
    QPoint metricPoint = this->m_isoMetric->GetMetricLocation(event->x(), event->y());
    this->m_objectCreator->MouseDown(metricPoint.x(), metricPoint.y());
}

void Scene::mouseReleaseEvent(const QMouseEvent *event)
{

}

void Scene::mouseMoveEvent(const QMouseEvent *event)
{

}
