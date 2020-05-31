/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef ISOMETRIC_H
#define ISOMETRIC_H


#include <QPixmap>
#include <QPair>

/*!
 * \class Isometric
 * \brief The Isometric class
 */
class Isometric
{

public:
    Isometric(void);
    virtual ~Isometric();

    int defaultIsometricWidth();
    int defaultIsometricHeight();
    int defaultIsometricHarfWidth();
    int defaultIsometricHarfHeight();
    QVector<int> *defaultIsometricMouseMapData();


private:
    const static int METRIC_WIDTH_2657 = 40;
    const static int METRIC_HEIGH_2657 = 20;
    const static int METRIC_HARF_WIDTH_2657 = 20;
    const static int METRIC_HARF_HEIGH_2657 = 10;

    const static int METRIC_WIDTH_30 = 20;
    const static int METRIC_HEIGH_30 = 20;
    const static int METRIC_HARF_WIDTH_30 = 10;
    const static int METRIC_HARF_HEIGH_30 = 10;

private:
    int m_defaultIsometricWidth;
    int m_defaultIsometricHeight;
    int m_defaultIsometricHarfWidth;
    int m_defaultIsometricHarfHeight;
    QVector<int> *m_defaultMouseMapData;

    int m_metricX;       // 메트릭 X 위치
    int m_metricY;       // 메트릭 Y 위치
    int m_metricPixelX;  // 메트릭 픽셀 X 시작 위치
    int m_metricPixelY;  // 메트릭 픽셀 Y 시작 위치

    int m_regionX;  // 메트릭 X좌표
    int m_regionY;  // 메트릭 Y좌표
    int m_offX;     // 메트릭 X좌표의 오프셋좌표
    int m_offY;     // 메트릭 Y좌표의 오프셋좌표

    QPixmap m_marker;  // 아래 데이타에 맞는 마우스 포인터 이미지

    /*!
     * 마름모 크기 : 40 x 20
     * 마름모 각도 : 26.565 도
     *
     * Inkscape 사용시 아래와 같이 설정한다.
     * 파일 -> 문서속성 -> 격자
     * 생성 : 마름모격자
     * 격자단위 : px
     * 기본 X : 0.0
     * 기본 Y : 0.0
     * 여백 Y : 20.0
     * X 각도 : 26.57 (0.005도 차이가 있음)
     * Y 각도 : 26.57 (0.005도 차이가 있음)
     */
    const int m_mouseMapData_2657[METRIC_HEIGH_2657][METRIC_WIDTH_2657] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4},
        {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    };

    /*!
     * 마름모 각도 30도 (일반적으로 많이 사용하는 매트릭)
     */
    const int m_mouseMapData_30[METRIC_HEIGH_30][METRIC_WIDTH_30]
        = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
           {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
           {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
           {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2},
           {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2},
           {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2},
           {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
           {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2},
           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
           {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4},
           {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4},
           {3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4},
           {3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4},
           {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4},
           {3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4},
           {3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4},
           {3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4},
           {3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
           {3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

public:
    void SetLocation(int mouseX, int mouseY);
    QPoint GetCurrentMetricLocation();
    QRect GetCurrentMetricPixel();
    void DrawMouseMarker(QPainter *painter);
    QPoint GetMetricPixel(int metricX, int metricY);
    QPoint GetMetricLocation(int mouseX, int mouseY);


private:
    void CalculateMetricPosition(int x, int y);
    void CalculateMetricZone();
    void CalculateMetricPixel();
    void GetPixelFromMetricZone(int zoneNumber);

    void MouseMoveEvent(int mouseX, int mouseY);

};

#endif // ISOMETRIC_H

