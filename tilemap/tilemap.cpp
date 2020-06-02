/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */


#include "tilemap/tilemap.h"
#include "coordinatesystem/isometric.h"

#include <QString>
#include <QImageReader>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QtCore/QtMath>
#include <math.h>



TileMap::TileMap(Isometric *isoMetric)
{
    this->m_outsideBorderLocation = new int[4]{0, 0, 0, 0};

    this->m_isoMetric = isoMetric;

    this->m_defaultTileMapImage = new QPixmap();
    this->m_tileMapLine = new QPixmap();

    // TODO : 환경설정으로 이동
    QString tileLineImage, tileMapImage;

    if (this->m_isoMetric->defaultIsometric() == Isometric::METRIC_30) {
        tileLineImage = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/"
                        "배경타일라인30.png";
        tileMapImage
            = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일맵30.png";
    } else if (this->m_isoMetric->defaultIsometric() == Isometric::METRIC_2657) {
        tileLineImage
            = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일라인.png";
        tileMapImage
            = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일맵.png";
    }
    this->m_defaultTileMapImage = LoadTileImage(tileMapImage);
    this->m_tileMapLine = LoadTileImage(tileLineImage);
    this->m_tileImageMetricLocation = new QPoint(0, 0);
    this->m_mapDataMetricLocation = new QPoint(0, 0);
}

/*!
 * \brief TileMap::LoadTileImage 이미지 파일을 읽어 QPixmap으로 리턴하는 함수
 * \param fileName
 * \return
 */
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


/*!
 * \brief TileMap::SetTileImage 이미지 파일을 읽어 타일맵으로 설정하고, 맵데이타를 생성하는 함수
 * \param fileName
 */
void TileMap::SetTileImage(QString fileName) {
    this->m_tileMapImage = LoadTileImage(fileName);
    InitTilemapData(this->m_tileMapImage->size());
}


/*!
 * \brief TileMap::SetScreenSize 스크린 정보를 설정하는 함수, 스크린 사이즈와 매트릭정보를 설정한다.
 * \param screenSize
 */
void TileMap::SetScreenSize(QRect screenSize)
{
    this->m_screenSize = screenSize;

    // 스크린 사이즈를 ISO Metric 단위로 변환한다.
    int metricWidth = ceil((double)(this->m_screenSize.width()) /
                               (double)this->m_isoMetric->defaultIsometricWidth());
    int metricHeight = ceil((double)(this->m_screenSize.height()*2) /
                            (double)this->m_isoMetric->defaultIsometricHeight());

    // 스크린 사이즈를 매트릭 사이즈로 변환된 값을 저장한다.
    this->m_screenMetricSize.setWidth(metricWidth);
    this->m_screenMetricSize.setHeight(metricHeight);

    // 스크린 테두리를 지정한다.
    this->m_outsideBorderLocation[TileMap::BORDER_TOP] = 0;
    this->m_outsideBorderLocation[TileMap::BORDER_BOTTOM] = metricHeight-2;
    this->m_outsideBorderLocation[TileMap::BORDER_LEFT] = 0;
    this->m_outsideBorderLocation[TileMap::BORDER_RIGHT] = metricWidth-2;
}


/*!
 * \brief TileMap::InitTilemapData 타일맵 이미지에 맞는 타일맵 데이타를 생성하는 함수
 * \param tileImageSize
 */
void TileMap::InitTilemapData(QSize tileImageSize)
{
    int metricWidth = ceil((double)(tileImageSize.width()) /
                           (double)this->m_isoMetric->defaultIsometricWidth());
    int metricHeight = ceil((double)(tileImageSize.height()*2) /
                            (double)this->m_isoMetric->defaultIsometricHeight());

    for(int i=0; i<metricHeight; i++) {
        this->m_tileMapData.append(QVector<int>(metricWidth));
    }

    this->m_tileMapDataSize = new QSize(metricWidth, metricHeight);
}


/*!
 * \brief TileMap::GetOutsideBorderLocation 스크린 영역의 가장자리 정보를 리턴하는 함수
 * \return
 */
int *TileMap::GetOutsideBorderLocation() {
    return this->m_outsideBorderLocation;
}


/*!
 * \brief TileMap::OptionShowDefaultTileMapImage 기본 타일맵 이미지 보여주기
 * \param bShow
 */
void TileMap::OptionShowDefaultTileMapImage(bool bShow)
{
    this->m_bShowDefaultTileMapImage = bShow;
}


/*!
 * \brief TileMap::OptionShowTileMapLine 타일맵 선 보여주기
 * \param bShowLine
 */
void TileMap::OptionShowTileMapLine(bool bShowLine)
{
    this->m_bShowTileMapLine = bShowLine;
}


/*!
 * \brief TileMap::OptionShowTileData 타일맵 데이타 보여주기
 * \param bShowData
 */
void TileMap::OptionShowTileData(bool bShowData) {
    this->m_bShowTileData = bShowData;
}


/*!
 * \brief TileMap::OptionScroll 타일맵 스크롤 여부
 * \param bScroll
 */
void TileMap::OptionScroll(bool bScroll) {
    this->m_bScroll = bScroll;
}


/*!
 * \brief TileMap::DrawTilemap 타일맵을 그리는 함수
 * 1. 기본 배경이미지 그리기
 * 2. 사용자 지정 이미지 그리기
 * 3. 타일맵 라인 그리기
 * 4. 타일맵 데이타 그리기
 * \param painter
 */
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


/*!
 * \brief TileMap::DrawDefaultTilemap 기본 타일맵 이미지를 그리는 함수
 * \param painter
 */
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


/*!
 * \brief TileMap::DrawScrollTilemap 스크롤 타일맵을 그리는 함수
 * \param painter
 */
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
            painter->drawPixmap(pixel.x() - this->m_isoMetric->defaultIsometricHarfWidth(),
                                pixel.y(),
                                *this->m_tileMapImage);
        } else
            painter->drawPixmap(pixel.x(), pixel.y(), *this->m_tileMapImage);

        m_tileImageMetricLocation->setX(x);
        m_tileImageMetricLocation->setY(y);
    } else {
        painter->drawPixmap(0, 0, *this->m_tileMapImage);
    }
}


/*!
 * \brief TileMap::DrawTilemapLine 타일맵 라인을 그리는 함수
 * \param painter
 */
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


/*!
 * \brief TileMap::DrawMTilemapData 타일맵 데이타를 그리는 함수
 * \param painter
 */
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
                    painter->drawText(QRect(point.x() + this->m_isoMetric->defaultIsometricHarfWidth() - 2,
                                            point.y() + this->m_isoMetric->defaultIsometricHarfHeight() - 5,
                                            20, 20),
                                      0,
                                      QString::number(this->m_tileMapData[i][j]));
                }
            }
        }
    }
}


/*!
 * \brief TileMap::BorderTouchEvent 스크린 상의 가장자리 (위,아래,왼쪽,오른쪽)을 터치했는지 알 수 있는 함수
 * \param touchBorderDir
 */
void TileMap::BorderTouchEvent(int touchBorderDir) {
    m_touchBoderDirection = touchBorderDir;
}


/*!
 * \brief TileMap::GetMetricDataLocation 마우스가 위치한 곳의 맵데이터의 위치를 구하는 함수
 * \param metricX
 * \param metricY
 * \return
 */
QPoint *TileMap::GetMetricDataLocation(int metricX, int metricY) {
    if(metricX < 0 || metricY < 0) return nullptr;
    if(this->m_tileMapData.length() <= 0) return nullptr;

#ifdef DEBUG
    qDebug() << "Screen Location: X: " << metricX << ", Y: " << metricY;
    qDebug() << "Metric Start Location: X: " << qFabs(this->m_tileImageMetricLocation->x())
             << ", Y: " << qFabs(this->m_tileImageMetricLocation->y());
#endif

    int dataMapLocationX = qFabs(this->m_tileImageMetricLocation->x()) + metricX;
    int dataMapLocationY = qFabs(this->m_tileImageMetricLocation->y()) + metricY;

    if(dataMapLocationX < 0 || dataMapLocationY < 0) return nullptr;

    this->m_mapDataMetricLocation->setX(dataMapLocationX);
    this->m_mapDataMetricLocation->setY(dataMapLocationY);

    qDebug() << "Map data Location: X: " << dataMapLocationX << ", Y: " << dataMapLocationY;

    return this->m_mapDataMetricLocation;
}


/*!
 * \brief TileMap::GetDataMetricDataLocation 매트릭 데이타의 좌표 데이타를 구하는 함수.
 * \param metricX
 * \param metricY
 * \return
 */
int TileMap::GetDataMetricDataLocation(int mapDataMetricX, int mapDataMetricY)
{
    return this->m_tileMapData[mapDataMetricY][mapDataMetricX];
}

