/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "IsoMetric.h"
#include "tilemap.h"

#include <QPainter>
#include <QRect>


class MainCamera
{
public:
    MainCamera();


private:
    IsoMetric *m_isoMetric;
    TileMap *m_tileMap;
    QBrush *m_backgroundColor;
    QRect m_backgroundSize;
    QPixmap m_backgroundDefaultImage;

public:
    QPainter *m_mainPainter;


public:
    IsoMetric *GetIsoMetric();
    TileMap *GetTileMap();

    void SetBackgroundColor(QBrush *brush);
    void SetSize(QRect rect);
    void OptionShowTileMap(bool bShowTileMap, bool bShowTileMapLine);
    void OptionShowTileData(bool bShowTileData);
    void Draw(QPaintDevice *device, QPoint *mousePoint);


public:
    bool m_bDrawBackgroundImage;  // 이미지로 배경 채우기 (false: 채우지 않는다. true: 채운다)


private:

};

#endif // DRAWMANAGER_H
