/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include "coordinatesystem/isometric.h"
#include "tilemap/tilemap.h"

#include <QPainter>
#include <QRect>

#include <factory/objectmanager.h>

#include <scene/scene.h>

/*!
 * \class MainCamera
 * \brief The MainCamera class
 */
class MainCamera
{
public:
    MainCamera(Isometric *);
    ~MainCamera();


private:
    Isometric *m_isoMetric;
    TileMap *m_tileMap;
    QBrush *m_backgroundColor;
    QRect m_backgroundSize;
    QPixmap m_backgroundDefaultImage;
    ObjectManager *m_objManager;

public:
    Isometric *GetIsoMetric();
    TileMap *GetTileMap();
    ObjectManager *GetObjectCreator();

    void SetBackgroundColor(QBrush *brush);
    void SetScreenSize(QRect rect);

    void OptionShowDefaultTileMapImage(bool);
    void OptionShowTileMapLine(bool);
    void OptionShowTileData(bool);

    void Draw(QPaintDevice *device, QPoint *mousePoint);


public:
    bool m_bDrawBackgroundImage;  // 이미지로 배경 채우기 (false: 채우지 않는다. true: 채운다)


private:

};

#endif // DRAWMANAGER_H
