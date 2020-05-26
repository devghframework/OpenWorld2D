/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
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
#include <tuple>


#define DEBUG


TileMap::TileMap(IsoMetric *isoMetric)
{
    this->m_isoMetric = isoMetric;

    this->m_tileMap = new QPixmap();
    this->m_tileMapLine = new QPixmap();

    // TODO : 환경설정으로 이동
    const QString tileLineImage = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일라인.png";
    const QString tileMapImage= "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/배경타일맵.png";
    this->m_tileMap = LoadTileImage(tileMapImage);
    this->m_tileMapLine = LoadTileImage(tileLineImage);

     QPair<int, int> pair = this->m_isoMetric->GetMetricPixel(0, 0);
     QPair<int, int> pair2 = this->m_isoMetric->GetMetricPixel(0, 1);

     qDebug("(%d, %d)", pair.first, pair.second);
     qDebug("(%d, %d)", pair2.first, pair2.second);
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


void TileMap::SetSize(QRect tileSize)
{
    this->m_tileSize = tileSize;

    // 타일 메모리맵 데이타 크기를 설정하고 데이타를 초기화 한다.
    int width = ceil((double)(this->m_tileSize.width()*2) / (double)IsoMetric::METRIC_WIDTH);
    int height = ceil((double)(this->m_tileSize.height()*2) / (double)IsoMetric::METRIC_HEIGH);

    for(int i=0; i<height; i++) {
        this->m_tileData.append(QVector<int>(width));
    }
}


void TileMap::OptionShowTileMap(bool bShow)
{
    this->m_bShowTileMap = bShow;
}


void TileMap::OptionShowTileMapLine(bool bShowLine)
{
    this->m_bShowTileMapLine = bShowLine;
}

void TileMap::OptionShowTileData(bool bShowData) {
    this->m_bShowTileData = bShowData;
}

void TileMap::DrawTilemap(QPainter *painter)
{
    // 배경 이미지를 바둑판 모양으로 채운다.
    if(this->m_bShowTileMap) {
        if(this->m_tileMap) {
            int x =0, y=0;
            do {
                painter->drawPixmap(x, y, *this->m_tileMap);
                x += this->m_tileMap->width();
                if(x >= this->m_tileSize.width()) {
                    x = 0;
                    y += this->m_tileMap->height();
                }
            } while(x<this->m_tileSize.width() && y<this->m_tileSize.height());
        }
    }

    // 타일 선 이미지를 바둑판 모양으로 채운다.
    if(this->m_bShowTileMapLine) {
        if(this->m_tileMapLine) {
            int x =0, y=0;
            do {
                painter->drawPixmap(x, y, *this->m_tileMapLine);
                x += this->m_tileMapLine->width();
                if(x >= this->m_tileSize.width()) {
                    x = 0;
                    y += this->m_tileMapLine->height();
                }
            } while(x<this->m_tileSize.width() && y<this->m_tileSize.height());
        }
    }

    // 타일 맵 데이타를 화면에 출력한다.
    if(this->m_bShowTileData) {
        if(this->m_tileData.length()>0) {
            QFont font = painter->font();
            font.setPixelSize(8);
            painter->setFont(font);
            for(int i=0; i<this->m_tileData.length(); i++) {
                for(int j=0; j<this->m_tileData[i].length(); j++) {
                    QPair<int, int> pair = this->m_isoMetric->GetMetricPixel(j, i);
                    painter->drawText(QRect(pair.first + IsoMetric::METRIC_HARF_WIDTH - 2,
                                            pair.second + IsoMetric::METRIC_HARF_HEIGH - 5,
                                            20, 20),
                                      0,
                                      QString::number(this->m_tileData[i][j]));
                }
            }
        }
    }
}


/*!
 * \brief TileMap::GetDataMetricLocation 매트릭 좌표의 데이타를 리턴한다.
 * \param metricX
 * \param metricY
 * \return
 */
int TileMap::GetDataMetricLocation(int metricX, int metricY) {
    return this->m_tileData[metricY][metricX];
}
