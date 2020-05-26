/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "IsoMetric.h"
#include "qdebug.h"
#include <QPainter>
#include <QString>
#include <QImageReader>
#include <QImage>
#include <QPair>

#define DEBUG

IsoMetric::IsoMetric() {
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


IsoMetric::~IsoMetric() {

}


/*!
 * 마우스 위치에 대한 상대적 메트릭 위치를 계산한다.
 * \brief IsoMetric::SetMetric
 * \param x
 * \param y
 */
void IsoMetric::CalculateMetricPosition(int mouseX, int mouseY) {
    this->m_regionX = mouseX / METRIC_WIDTH;
    this->m_regionY = (mouseY / METRIC_HEIGH) * 2;
    this->m_offX = mouseX % METRIC_WIDTH;
    this->m_offY = mouseY % METRIC_HEIGH;
}


/*!
 * 마우스맵 데이타에 해당하는 매트릭 존 위치를 계산하는 함수
 * \brief IsoMetric::CalculateMetricZone
 */
void IsoMetric::CalculateMetricZone() {
    int regionDx = 0;
    int regionDy = 0;

    // 마우스가 위치한 마커 데이타를 가져온다.
    int posMouseMap = this->m_mouseMap[this->m_offY][this->m_offX];

    // 데이타에 따른 마우스의 매트릭 위치를 이동한다.
    switch (posMouseMap) {
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
void IsoMetric::SetMetricZone() {
    this->m_metricPixelX = 0;
    this->m_metricPixelY = 0;
    if ((this->m_metricY % 2) == 0) {
        this->m_metricPixelX = this->m_metricX * METRIC_WIDTH;
        this->m_metricPixelY = this->m_metricY * (METRIC_HEIGH / 2);
    } else {
        this->m_metricPixelX = (this->m_metricX * METRIC_WIDTH) + (METRIC_WIDTH / 2);
        this->m_metricPixelY = this->m_metricY * (METRIC_HEIGH / 2);
    }
}

/*!
 * \brief IsoMetric::GetMetricPixel 매트릭 좌표의 픽셀 좌표를 계산하는 함수.
 * \param metricX
 * \param metricY
 * \return
 */
QPair<int, int> IsoMetric::GetMetricPixel(int metricX, int metricY) {
    int metricPixelX = 0;
    int metricPixelY = 0;
    if ((metricY % 2) == 0) {
        metricPixelX = metricX * METRIC_WIDTH;
        metricPixelY = metricY * (METRIC_HEIGH / 2);
    } else {
        metricPixelX= (metricX * METRIC_WIDTH) + (METRIC_WIDTH / 2);
        metricPixelY = metricY * (METRIC_HEIGH / 2);
    }

    QPair<int, int> pair(metricPixelX, metricPixelY);
    return pair;
}

/*!
 * \brief IsoMetric::GetMetricLocation 마우스 좌표를 매트릭 좌표로 변환하는 함수.
 * \param mouseX
 * \param mouseY
 * \return
 */
QPair<int, int> IsoMetric::GetMetricLocation(int mouseX, int mouseY)
{
    int regionX = mouseX / METRIC_WIDTH;
    int regionY = (mouseY / METRIC_HEIGH) * 2;
    int offX = mouseX % METRIC_WIDTH;
    int offY = mouseY % METRIC_HEIGH;

    int regionDx = 0;
    int regionDy = 0;

    // 마우스가 위치한 마커 데이타를 가져온다.
    int posMouseMap = this->m_mouseMap[offY][offX];

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

    QPair<int, int> pair(metricX, metricY);
    return pair;
}

/*!
 * 마우스 이동 이벤트 함수
 * \brief IsoMetric::MouseMove
 */
void IsoMetric::MouseMoveEvent(int mouseX, int mouseY) {

    CalculateMetricPosition(mouseX, mouseY);
    CalculateMetricZone();
    SetMetricZone();
}


/*!
 * 마우스 위치에 해당하는 매트릭 위치를 계산한다.
 * \brief IsoMetric::SetLocation
 * \param mouseX
 * \param mouseY
 */
void IsoMetric::SetLocation(int mouseX, int mouseY) {
    MouseMoveEvent(mouseX, mouseY);
}

/*!
 * \brief IsoMetric::GetLocation 현재 마우스가 위치한 곳의 매트릭좌표를 리턴한다.
 * \return
 */
QPair<int, int> IsoMetric::GetCurrentMetricLocation() {
    QPair<int, int> pair(this->m_metricX, this->m_metricY);
    return pair;
}

QRect IsoMetric::GetCurrentMetricPixel() {
    QRect rect(this->m_metricPixelX, this->m_metricPixelY, METRIC_WIDTH, METRIC_HEIGH);
    return rect;
}

/*!
 * 마우스 위치에 마커를 표시한다.
 * \brief IsoMetric::DrawMetric
 * \param painter
 */
void IsoMetric::DrawMouseMarker(QPainter *painter) {
    painter->drawPixmap(this->m_metricPixelX, this->m_metricPixelY, this->m_marker);
}
