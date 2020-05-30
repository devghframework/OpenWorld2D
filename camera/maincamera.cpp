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

#include <QPainter>
#include <QRect>
#include <QImageReader>
#include <QBrush>
#include <QColor>

//#define DEBUG

MainCamera::MainCamera(Isometric *isometric)
{
    this->m_isoMetric = isometric;
    this->m_bDrawBackgroundImage = true;
    this->m_tileMap = new TileMap(this->m_isoMetric);
    this->m_backgroundColor = new QBrush(QColor(Qt::black));
    this->m_objManager = new ObjectManager();
}


MainCamera::~MainCamera()
{
}


Isometric *MainCamera::GetIsoMetric() {
    return this->m_isoMetric;
}


TileMap *MainCamera::GetTileMap() {
    return this->m_tileMap;
}


ObjectManager *MainCamera::GetObjectCreator()
{
    return this->m_objManager;
}


void MainCamera::SetScreenSize(QRect rect) {
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
    // m_objManager->DrawObjects(&painter);
}
