/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "maincamera.h"
#include <QPainter>
#include <QRect>
#include <QImageReader>
#include <QBrush>
#include <QColor>

#define DEBUG

MainCamera::MainCamera()
{
    this->m_isoMetric = new IsoMetric();
    this->m_bDrawBackgroundImage = true;
    this->m_tileMap = new TileMap(this->m_isoMetric);
    this->m_backgroundColor = new QBrush(QColor(Qt::black));
}

IsoMetric *MainCamera::GetIsoMetric() {
    return this->m_isoMetric;
}

TileMap *MainCamera::GetTileMap() {
    return this->m_tileMap;
}

void MainCamera::SetSize(QRect rect) {
    this->m_backgroundSize = rect;
    this->m_tileMap->SetSize(rect);
}

void MainCamera::OptionShowTileMap(bool bShowTileMap, bool bShowTileMapLine) {
    this->m_tileMap->OptionShowTileMap(bShowTileMap);
    this->m_tileMap->OptionShowTileMapLine(bShowTileMapLine);
}

void MainCamera::OptionShowTileData(bool bShowTileData) {
    this->m_tileMap->OptionShowTileData(bShowTileData);
}

void MainCamera::SetBackgroundColor(QBrush *brush) {
    this->m_backgroundColor = brush;
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
}
