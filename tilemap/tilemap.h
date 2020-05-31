/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include "coordinatesystem/isometric.h"

#include <QtCore>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QVector>

/*!
 * \class TileMap
 * \brief The TileMap class
 */
class TileMap
{
    Q_GADGET


public:
    TileMap(Isometric *isoMetric);

    /*!
     * \brief The BORDER_DIR 테두리 방향
     */
    enum BORDER_DIR {
        BORDER_NONE = -1,
        BORDER_TOP,
        BORDER_BOTTOM,
        BORDER_LEFT,
        BORDER_RIGHT
    };
    Q_ENUM(BORDER_DIR)


private:
    Isometric *m_isoMetric;
    QPixmap *m_defaultTileMapImage = nullptr;
    QPixmap *m_tileMapImage = nullptr;
    QPixmap *m_tileMapLine = nullptr;
    QRect m_screenSize;
    QSize m_screenMetricSize;
    QVector<QVector<int>> m_tileMapData;
    QSize *m_tileMapDataSize;

    // 테두리 데이타가 따로 지정되지 않았을 경우 기본으로 사용되는 데이타이다.
    // BORDER_DIR 값을 가진다.
    int *m_outsideBorderLocation;

    QPoint *m_tileImageMetricLocation; // 타일 이미지가 화면에 출력되는 시작 매트릭 좌표
    QPoint *m_mapDataMetricLocation;  // 현재 마우스가 위치한 맵데이타의 좌표
    int m_touchBoderDirection;


private:
    /*****************************************************************************
     * 타일맵 옵션 변수들
     *****************************************************************************/
    /*!
     * \brief m_bShowTileMap [옵션] 기본 타일맵을 화면에 보이기 (false: 보이지 않음, true: 보임)
     */
    bool m_bShowDefaultTileMapImage = false;

    /*!
     * \brief m_bShowTileMapLine  [옵션] 타일맵선을 화면에 보이기 (false: 보이지 않음, true: 보임)
     */
    bool m_bShowTileMapLine = false;

    /*!
     * \brief m_bShowTileData [옵션] 타일맵에 할당된 데이타 보이기  (false: 보이지 않음, true: 보임)
     */
    bool m_bShowTileData = false;

    /*!
     * \brief m_bScroll [옵션] 맵이미지가 화면크기보다 클 경우 스크롤 여부 (false: 스크롤 불가, true: 스크롤 가능)
     */
    bool m_bScroll = false;


private:
    void InitTilemapData(QSize tileImageSize);
    void DrawDefaultTilemap(QPainter *);
    void DrawScrollTilemap(QPainter *);
    void DrawTilemapLine(QPainter *);
    void DrawMTilemapData(QPainter *);


public:
    QPixmap *LoadTileImage(QString);
    void SetTileImage(QString fileName);
    void SetScreenSize(QRect);
    void DrawTilemap(QPainter *);

    QPoint *GetMetricDataLocation(int, int);
    int GetDataMetricDataLocation(int, int);
    void BorderTouchEvent(int touchBorderDir);
    int *GetOutsideBorderLocation();

    void OptionShowDefaultTileMapImage(bool);
    void OptionShowTileMapLine(bool);
    void OptionShowTileData(bool);
    void OptionScroll(bool);

};

#endif // TILEMAP_H
