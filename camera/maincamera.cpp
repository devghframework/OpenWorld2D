/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "camera/maincamera.h"
#include "scene/scene.h"
#include "scene/scenemanager.h"

#include <QBrush>
#include <QColor>
#include <QImageReader>
#include <QPainter>
#include <QRect>

MainCamera::MainCamera(Isometric *isometric, SceneManager *sceneManager)
{
    this->m_isoMetric = isometric;
    this->m_sceneManager = sceneManager;

    this->m_bDrawBackgroundImage = true;

    InitMainCamera();
}


MainCamera::~MainCamera()
{
    this->m_tileMap = nullptr;
    this->m_backgroundColor = nullptr;

    delete this->m_tileMap;
    delete this->m_backgroundColor;
}

void MainCamera::InitMainCamera()
{
    this->m_tileMap = new TileMap(this->m_isoMetric);
    this->m_backgroundColor = new QBrush(QColor(Qt::black));
}

Isometric *MainCamera::GetIsoMetric()
{
    return this->m_isoMetric;
}

TileMap *MainCamera::GetTileMap()
{
    return this->m_tileMap;
}

void MainCamera::SetScreenSize(QRect rect)
{
    this->m_backgroundSize = rect;
    this->m_tileMap->SetScreenSize(rect);
}

void MainCamera::SetBackgroundColor(QBrush *brush) {
    this->m_backgroundColor = brush;
}


void MainCamera::OptionShowDefaultTileMapImage(bool bShow)
{
    this->m_tileMap->OptionShowDefaultTileMapImage(bShow);
}


void MainCamera::OptionShowTileMapLine(bool bShow)
{
    this->m_tileMap->OptionShowTileMapLine(bShow);
}


void MainCamera::OptionShowTileData(bool bShow)
{
    this->m_tileMap->OptionShowTileData(bShow);
}


void MainCamera::Draw(QPaintDevice *device, QPoint *mousePoint) {

    QPainter painter(device);

    // 배경색으로 지우기
    painter.fillRect(this->m_backgroundSize, *this->m_backgroundColor);

    // 배경 이미지를 바둑판 모양으로 채운다.
    this->m_tileMap->DrawTilemap(&painter);

    // ISO Metric 적용
    m_isoMetric->SetLocation(mousePoint->x(), mousePoint->y());
    m_isoMetric->DrawMouseMarker(&painter);

    // Scene 출력
    this->m_sceneManager->GetScene("1")->DrawScene(&painter);
}
