/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include "IsoMetric.h"

#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QVector>


class TileMap
{
public:
    TileMap(IsoMetric *isoMetric);

private:
    IsoMetric *m_isoMetric;
    QPixmap *m_tileMap = nullptr;
    QPixmap *m_tileMapLine = nullptr;
    QRect m_tileSize;
    QVector<QVector<int>> m_tileData;

private:
    /*****************************************************************************
     * 타일맵 옵션 변수들
     *****************************************************************************/
    /*!
     * \brief m_bShowTileMap [옵션] 타일맵을 화면에 보이기 (false: 보이지 않음, true: 보임)
     */
    bool m_bShowTileMap = false;

    /*!
     * \brief m_bShowTileMapLine  [옵션] 타일맵선을 화면에 보이기 (false: 보이지 않음, true: 보임)
     */
    bool m_bShowTileMapLine = false;

    /*!
     * \brief m_bShowTileData [옵션] 타일맵에 할당된 데이타 보이기  (false: 보이지 않음, true: 보임)
     */
    bool m_bShowTileData = false;

public:
    QPixmap *LoadTileImage(QString);
    void SetSize(QRect);
    void DrawTilemap(QPainter *);
    int GetDataMetricLocation(int metricX, int metricY);

    void OptionShowTileMap(bool);
    void OptionShowTileMapLine(bool);
    void OptionShowTileData(bool);
};

#endif // TILEMAP_H
