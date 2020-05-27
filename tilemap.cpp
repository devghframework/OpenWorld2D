/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */


#include "tilemap.h"
#include "IsoMetric.h"

#include <QString>
#include <QImageReader>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QtCore/QtMath>
#include <math.h>

#define DEBUG


TileMap::TileMap(IsoMetric *isoMetric)
{
    this->m_outsideBorderLocation = new int[4]{0, 0, 0, 0};

    this->m_isoMetric = isoMetric;

    this->m_defaultTileMapImage = new QPixmap();
    this->m_tileMapLine = new QPixmap();

    // TODO : 환경설정으로 이동
    const QString tileLineImage = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일라인.png";
    const QString tileMapImage= "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일맵.png";
    this->m_defaultTileMapImage = LoadTileImage(tileMapImage);
    this->m_tileMapLine = LoadTileImage(tileLineImage);
    this->m_tileImageMetricLocation = new QPoint(0, 0);
    this->m_mapDataMetricLocation = new QPoint(0, 0);
}

QPixmap *TileMap::LoadTileImage(QString fileName)
{
    QPixmap *pixMap = new QPixmap();
    QImageReader r(fileName);
    r.setDecideFormatFromContent(true);
    QImage i = r.read();
    if (!i.isNull()) {
       *pixMap = QPixmap::fromImage(i);
    }
    else {
#ifdef DEBUG
    qDebug("마우스 포인터 이미지를 읽을 수 없습니다.");
    //libpng warning: iCCP: CRC error : 이미지 포멧이 잘못 되었을 경우
#endif
    }
    return pixMap;
}


void TileMap::SetTileImage(QString fileName) {
    this->m_tileMapImage = LoadTileImage(fileName);
    InitTilemapData(this->m_tileMapImage->size());
}


void TileMap::SetScreenSize(QRect screenSize)
{
    this->m_screenSize = screenSize;

    // 스크린 사이즈를 ISO Metric 단위로 변환한다.
    int metricWidth = ceil((double)(this->m_screenSize.width()) / (double)IsoMetric::METRIC_WIDTH);
    int metricHeight = ceil((double)(this->m_screenSize.height()*2) / (double)IsoMetric::METRIC_HEIGH);

    // 스크린 사이즈를 매트릭 사이즈로 변환된 값을 저장한다.
    this->m_screenMetricSize.setWidth(metricWidth);
    this->m_screenMetricSize.setHeight(metricHeight);

    // 스크린 테두리를 지정한다.
    this->m_outsideBorderLocation[TileMap::BORDER_TOP] = 0;
    this->m_outsideBorderLocation[TileMap::BORDER_BOTTOM] = metricHeight-2;
    this->m_outsideBorderLocation[TileMap::BORDER_LEFT] = 0;
    this->m_outsideBorderLocation[TileMap::BORDER_RIGHT] = metricWidth-2;
}


void TileMap::InitTilemapData(QSize tileImageSize)
{
    int metricWidth = ceil((double)(tileImageSize.width()) / (double)IsoMetric::METRIC_WIDTH);
    int metricHeight = ceil((double)(tileImageSize.height()*2) / (double)IsoMetric::METRIC_HEIGH);

    for(int i=0; i<metricHeight; i++) {
        this->m_tileMapData.append(QVector<int>(metricWidth));
    }

    this->m_tileMapDataSize = new QSize(metricWidth, metricHeight);
}


int *TileMap::GetOutsideBorderLocation() {
    return this->m_outsideBorderLocation;
}


void TileMap::OptionShowDefaultTileMapImage(bool bShow)
{
    this->m_bShowDefaultTileMapImage = bShow;
}


void TileMap::OptionShowTileMapLine(bool bShowLine)
{
    this->m_bShowTileMapLine = bShowLine;
}


void TileMap::OptionShowTileData(bool bShowData) {
    this->m_bShowTileData = bShowData;
}


void TileMap::OptionScroll(bool bScroll) {
    this->m_bScroll = bScroll;
}


void TileMap::DrawTilemap(QPainter *painter)
{
    // 기본 배경 이미지를 바둑판 모양으로 채운다.
    if(this->m_bShowDefaultTileMapImage) {
        if(this->m_defaultTileMapImage) {
            DrawDefaultTilemap(painter);
        }
    }

    // 사용자 지정 타일맵 이미지를 출력한다.
    if(this->m_tileMapImage) {
        DrawScrollTilemap(painter);
    }

    // 타일 선 이미지를 바둑판 모양으로 채운다.
    if(this->m_bShowTileMapLine) {
        if(this->m_tileMapLine) {
            DrawTilemapLine(painter);
        }
    }

    // 타일 맵 데이타를 화면에 출력한다.
    if(this->m_bShowTileData) {
        if(this->m_tileMapData.length()>0) {
            DrawMTilemapData(painter);
        }
    }
}


void TileMap::DrawDefaultTilemap(QPainter *painter)
{
    int x =0, y=0;
    do {
        painter->drawPixmap(x, y, *this->m_defaultTileMapImage);
        x += this->m_defaultTileMapImage->width();
        if(x >= this->m_screenSize.width()) {
            x = 0;
            y += this->m_defaultTileMapImage->height();
        }
    } while(x<this->m_screenSize.width() && y<this->m_screenSize.height());
}


void TileMap::DrawScrollTilemap(QPainter *painter) {

    if(this->m_bScroll)
    {
        int x = m_tileImageMetricLocation->x();
        int y = m_tileImageMetricLocation->y();

        // 타일이미지가 화면 영역 밖으로 이동하지 않게 조정한다.
        switch (m_touchBoderDirection) {
        case TileMap::BORDER_TOP:
            y--;
            if(qFabs(y) >= (this->m_tileMapDataSize->height() - this->m_screenMetricSize.height()))
                y++;
            break;
        case TileMap::BORDER_BOTTOM:
            y++;
            if(qFabs(y)<=1)
                y = 0;
            break;
        case TileMap::BORDER_LEFT:
            x--;
            if (qFabs(x) >= (this->m_tileMapDataSize->width() - this->m_screenMetricSize.width())) {
                x ++;
            }
            break;
        case TileMap::BORDER_RIGHT:
            x++;
            if(qFabs(x) <= 1)
                x = 0;
            break;
        default: break;
        }

//        int freeSpace = (this->m_tileMapDataSize->height() - this->m_screenMetricSize.height());
//        qDebug() << "TileDataSize : " << this->m_tileMapDataSize->height()
//                 << ", Location: " << qFabs(y)
//                 << ", free space: " << freeSpace - qFabs(y)
//                 << ", Screen Size: " << this->m_screenMetricSize.height();

        QPoint pixel;
        pixel = this->m_isoMetric->GetMetricPixel(x, y);

        if(y % 2 != 0) {
            // 위아래 스크롤시 화면 흔들림 방지를 위해 보정을 했으나,
            // 데이타 맵도 같이 보정해 줘야 한다.
            // Isometric 좌표도 동시에 변경해야 하는데, 가능한지
            painter->drawPixmap(pixel.x() - IsoMetric::METRIC_HARF_WIDTH, pixel.y(), *this->m_tileMapImage);
        } else
            painter->drawPixmap(pixel.x(), pixel.y(), *this->m_tileMapImage);

        m_tileImageMetricLocation->setX(x);
        m_tileImageMetricLocation->setY(y);
    } else {
        painter->drawPixmap(0, 0, *this->m_tileMapImage);
    }
}


void TileMap::DrawTilemapLine(QPainter *painter)
{
    // 타일 선 이미지를 바둑판 모양으로 채운다.
    if(this->m_bShowTileMapLine) {
        if(this->m_tileMapLine) {
            int x =0, y=0;
            do {
                painter->drawPixmap(x, y, *this->m_tileMapLine);
                x += this->m_tileMapLine->width();
                if(x >= this->m_screenSize.width()) {
                    x = 0;
                    y += this->m_tileMapLine->height();
                }
            } while(x<this->m_screenSize.width() && y<this->m_screenSize.height());
        }
    }
}


void TileMap::DrawMTilemapData(QPainter *painter)
{
    if(this->m_bShowTileData) {
        if(this->m_tileMapData.length()>0) {
            QFont font = painter->font();
            font.setPixelSize(8);
            painter->setFont(font);
            for(int i=0; i<this->m_tileMapData.length(); i++) {
                for(int j=0; j<this->m_tileMapData[i].length(); j++) {
                    QPoint point = this->m_isoMetric->GetMetricPixel(j, i);
                    painter->drawText(QRect(point.x() + IsoMetric::METRIC_HARF_WIDTH - 2,
                                            point.y() + IsoMetric::METRIC_HARF_HEIGH - 5,
                                            20, 20),
                                      0,
                                      QString::number(this->m_tileMapData[i][j]));
                }
            }
        }
    }
}


void TileMap::BorderTouchEvent(int touchBorderDir) {
    m_touchBoderDirection = touchBorderDir;
}


QPoint *TileMap::GetMetricDataLocation(int metricX, int metricY) {
    if(metricX < 0 || metricY < 0) return nullptr;
    if(this->m_tileMapData.length() <= 0) return nullptr;

    qDebug() << "Screen Location: X: " << metricX << ", Y: " << metricY;
    qDebug() << "Metric Start Location: X: " << qFabs(this->m_tileImageMetricLocation->x())
             << ", Y: " << qFabs(this->m_tileImageMetricLocation->y());

    int dataMapLocationX = qFabs(this->m_tileImageMetricLocation->x()) + metricX;
    int dataMapLocationY = qFabs(this->m_tileImageMetricLocation->y()) + metricY;

    if(dataMapLocationX < 0 || dataMapLocationY < 0) return nullptr;

    this->m_mapDataMetricLocation->setX(dataMapLocationX);
    this->m_mapDataMetricLocation->setY(dataMapLocationY);

    qDebug() << "Map data Location: X: " << dataMapLocationX << ", Y: " << dataMapLocationY;

    return this->m_mapDataMetricLocation;
}


/*!
 * \brief TileMap::GetDataMetricDataLocation 매트릭 좌표의 데이타를 리턴한다.
 * \param metricX
 * \param metricY
 * \return
 */
int TileMap::GetDataMetricDataLocation(int mapDataMetricX, int mapDataMetricY)
{
    return this->m_tileMapData[mapDataMetricY][mapDataMetricX];
}

