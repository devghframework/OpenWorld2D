/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef ISOMETRIC_H
#define ISOMETRIC_H


#include <QPixmap>
#include <QPair>

class IsoMetric
{

public:
    IsoMetric(void);
    ~IsoMetric();


public:
    const static int METRIC_WIDTH = 40;
    const static int METRIC_HEIGH = 20;
    const static int METRIC_HARF_WIDTH = 20;
    const static int METRIC_HARF_HEIGH = 10;


private:
    int m_metricX;       // 메트릭스 X 위치
    int m_metricY;       // 메트릭스 Y 위치
    int m_metricPixelX;  // 메트릭스 픽셀 X 시작 위치
    int m_metricPixelY;  // 메트릭스 픽셀 Y 시작 위치

    int m_regionX;  // 메트릭스 X좌표
    int m_regionY;  // 메트릭스 Y좌표
    int m_offX;     // 메트릭스 X좌표의 오프셋좌표
    int m_offY;     // 메트릭스 Y좌표의 오프셋좌표

    QPixmap m_marker;  // 아래 데이타에 맞는 마우스 포인터 이미지

    const int m_mouseMap[20][40] = {
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2},
        { 1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2},
        { 1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2},
        { 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2},
        { 1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2},
        { 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2},
        { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
        { 3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4},
        { 3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4},
        { 3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4},
        { 3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4},
        { 3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4},
        { 3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4},
        { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    };


public:
    void SetLocation(int mouseX, int mouseY);
    QPair<int, int> GetCurrentMetricLocation();
    QRect GetCurrentMetricPixel();
    void DrawMouseMarker(QPainter *painter);
    QPair<int, int> GetMetricPixel(int metricX, int metricY);
    QPair<int, int> GetMetricLocation(int mouseX, int mouseY);


private:
    void CalculateMetricPosition(int x, int y);
    void CalculateMetricZone();
    void SetMetricZone();
    void GetPixelFromMetricZone(int zoneNumber);
    void MouseMoveEvent(int mouseX, int mouseY);

};

#endif // ISOMETRIC_H

