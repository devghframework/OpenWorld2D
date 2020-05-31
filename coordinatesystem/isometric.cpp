/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "coordinatesystem/isometric.h"
#include "qdebug.h"
#include <QPainter>
#include <QString>
#include <QImageReader>
#include <QImage>
#include <QVector>


Isometric::Isometric() {
    // 기본 매트릭 정보 설정
    this->m_defaultIsometricWidth = METRIC_WIDTH_2657;
    this->m_defaultIsometricHeight = METRIC_HEIGH_2657;
    this->m_defaultIsometricHarfWidth = METRIC_HARF_WIDTH_2657;
    this->m_defaultIsometricHarfHeight = METRIC_HARF_HEIGH_2657;
    this->m_defaultMouseMapData = new QVector<int>[this->m_defaultIsometricHeight];
    for (int i = 0; i < this->m_defaultIsometricHeight; i++) {
        for (int j = 0; j < this->m_defaultIsometricWidth; j++)
            this->m_defaultMouseMapData[i].append(this->m_mouseMapData_2657[i][j]);
    }

    this->m_metricX = 0;
    this->m_metricY = 0;

    // 마우스 마크 이미지를 설정한다.
    // TODO
    // 환경설정 기능으로 이동
    const QString mouseImgFile = "/Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/MouseMark.png";
    QImageReader r(mouseImgFile);
    r.setDecideFormatFromContent(true);
    QImage i = r.read();
    if (!i.isNull()) {
       this->m_marker = QPixmap::fromImage(i);
    }
    else {
#ifdef DEBUG
    qDebug("마우스 포인터 이미지를 읽을 수 없습니다.");
    //libpng warning: iCCP: CRC error : 이미지 포멧이 잘못 되었을 경우
#endif
    }
}


Isometric::~Isometric() {

}


int Isometric::defaultIsometricWidth()
{
    return this->m_defaultIsometricWidth;
}

int Isometric::defaultIsometricHeight()
{
    return this->m_defaultIsometricHeight;
}

int Isometric::defaultIsometricHarfWidth()
{
    return this->m_defaultIsometricHarfWidth;
}

int Isometric::defaultIsometricHarfHeight()
{
    return this->m_defaultIsometricHarfHeight;
}

QVector<int> *Isometric::defaultIsometricMouseMapData()
{
    return this->m_defaultMouseMapData;
}

/*!
 * 마우스 위치에 대한 상대적 메트릭 위치를 계산한다.
 * \brief IsoMetric::SetMetric
 * \param x
 * \param y
 */
void Isometric::CalculateMetricPosition(int mouseX, int mouseY) {
    this->m_regionX = mouseX / this->m_defaultIsometricWidth;
    this->m_regionY = (mouseY / this->m_defaultIsometricHeight) * 2;
    this->m_offX = mouseX % this->m_defaultIsometricWidth;
    this->m_offY = mouseY % this->m_defaultIsometricHeight;

#ifdef DEBUG
//    qDebug() << "MOUSE X, Y " << QString::number(mouseX) << ", " << QString::number(mouseY);
//    qDebug() << "REGION X, Y : " << QString::number(this->m_regionX) << ", "
//             << QString::number(this->m_regionY);
//    qDebug() << "OFFSET X, Y : " << QString::number(this->m_offX) << ", "
//             << QString::number(this->m_offY);
#endif
}


/*!
 * 마우스맵 데이타에 해당하는 매트릭 존 위치를 계산하는 함수
 * \brief IsoMetric::CalculateMetricZone
 */
void Isometric::CalculateMetricZone() {

    // 마우스가 위치한 마커 데이타를 가져온다.
    int posMouseMapData = this->m_defaultMouseMapData[this->m_offY][this->m_offX];

#ifdef DEBUG
//    qDebug() << "MouseMapData: " << QString::number(posMouseMapData);
#endif

    // 마우스 데이타맵 데이타 위치의 매트릭 위치로 이동한다.
    int regionDx = 0;
    int regionDy = 0;
    switch (posMouseMapData) {
        case 0: regionDx = 0; regionDy = 0; break;
        case 1: regionDx -= 1; regionDy -= 1; break;
        case 2: regionDy -= 1; break;
        case 3: regionDx -= 1; regionDy += 1; break;
        case 4: regionDy += 1; break;
        default: break;
    }

    this->m_metricX = this->m_regionX + regionDx;
    this->m_metricY = this->m_regionY + regionDy;
}


/*!
 * 옮겨진 마우스 위치에 해당하는 매트릭 시작 위치 (픽셀)를 계산한다.
 * \brief IsoMetric::SetMetricStartPoint
 */
void Isometric::CalculateMetricPixel() {
    this->m_metricPixelX = 0;
    this->m_metricPixelY = 0;
    if ((this->m_metricY % 2) == 0) {
        this->m_metricPixelX = this->m_metricX * this->m_defaultIsometricWidth;
        this->m_metricPixelY = this->m_metricY * this->m_defaultIsometricHarfHeight;
    } else {
        this->m_metricPixelX = (this->m_metricX * this->m_defaultIsometricWidth) + this->m_defaultIsometricHarfWidth;
        this->m_metricPixelY = this->m_metricY * this->m_defaultIsometricHarfHeight;
    }
}

/*!
 * \brief IsoMetric::GetMetricPixel 매트릭 좌표의 픽셀 좌표를 계산하는 함수.
 * \param metricX
 * \param metricY
 * \return
 */
QPoint Isometric::GetMetricPixel(int metricX, int metricY) {
    int metricPixelX = 0;
    int metricPixelY = 0;
    if ((metricY % 2) == 0) {
        metricPixelX = metricX * this->m_defaultIsometricWidth;
        metricPixelY = metricY * this->m_defaultIsometricHarfHeight;
    } else {
        metricPixelX= (metricX * this->m_defaultIsometricWidth) + this->m_defaultIsometricHarfWidth;
        metricPixelY = metricY * this->m_defaultIsometricHarfHeight;
    }

    QPoint point(metricPixelX, metricPixelY);
    return point;
}

/*!
 * \brief IsoMetric::GetMetricLocation 마우스 좌표를 매트릭 좌표로 변환하는 함수.
 * \param mouseX
 * \param mouseY
 * \return
 */
QPoint Isometric::GetMetricLocation(int mouseX, int mouseY)
{
//    int regionX = mouseX / METRIC_WIDTH;
//    int regionY = (mouseY / METRIC_HEIGH) * 2;
    int offX = mouseX % this->m_defaultIsometricWidth;
    int offY = mouseY % this->m_defaultIsometricHeight;

    int regionDx = 0;
    int regionDy = 0;

    // 마우스가 위치한 마커 데이타를 가져온다.
    int posMouseMap = this->m_defaultMouseMapData[offY][offX];

    // 데이타에 따른 마우스의 매트릭 위치를 이동한다.
    switch (posMouseMap) {
        case 0: regionDx = 0; regionDy = 0; break;
        case 1: regionDx -= 1; regionDy -= 1; break;
        case 2: regionDy -= 1; break;
        case 3: regionDx -= 1; regionDy += 1; break;
        case 4: regionDy += 1; break;
        default: break;
    }

    int metricX = this->m_regionX + regionDx;
    int metricY = this->m_regionY + regionDy;

    QPoint point(metricX, metricY);
    return point;
}

/*!
 * 마우스 이동 이벤트 함수
 * \brief IsoMetric::MouseMove
 */
void Isometric::MouseMoveEvent(int mouseX, int mouseY) {

    CalculateMetricPosition(mouseX, mouseY);
    CalculateMetricZone();
    CalculateMetricPixel();
}


/*!
 * 마우스 위치에 해당하는 매트릭 위치를 계산한다.
 * \brief IsoMetric::SetLocation
 * \param mouseX
 * \param mouseY
 */
void Isometric::SetLocation(int mouseX, int mouseY) {
    MouseMoveEvent(mouseX, mouseY);
}

/*!
 * \brief IsoMetric::GetLocation 현재 마우스가 위치한 곳의 매트릭좌표를 리턴한다.
 * \return
 */
QPoint Isometric::GetCurrentMetricLocation() {
    QPoint point(this->m_metricX, this->m_metricY);
    return point;
}

QRect Isometric::GetCurrentMetricPixel() {
    QRect rect(this->m_metricPixelX,
               this->m_metricPixelY,
               this->m_defaultIsometricWidth,
               this->m_defaultIsometricHeight);
    return rect;
}

/*!
 * 마우스 위치에 마커를 표시한다.
 * \brief IsoMetric::DrawMetric
 * \param painter
 */
void Isometric::DrawMouseMarker(QPainter *painter) {
    painter->drawPixmap(this->m_metricPixelX, this->m_metricPixelY, this->m_marker);
}
