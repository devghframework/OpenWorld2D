/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber


     오픈 월드 메인 위젯
 */

#include "openworldwidget/owdrawwidget.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QBrush>
#include <QColor>
#include <QGraphicsOpacityEffect>


/*!
 * \brief OWDrawWidget::OWDrawWidget 오픈월드 메인 위젯 생성자
 * \param parent
 */
OWDrawWidget::OWDrawWidget(QWidget* parent)
    : QWidget(parent)
{
    this->m_openWorldWidget = parent;
    //this->m_openWorldWidget->setFont(QFont ("Courier", 8));

    this->m_mainCamera = new MainCamera();
    this->m_mainCamera->OptionShowDefaultTileMapImage(true);
    this->m_mainCamera->OptionShowTileMapLine(true);
    this->m_mainCamera->OptionShowTileData(true);
    this->m_mousePoint = new QPoint(100, 100);  // 시작 마우스 위치
}


/*!
 * \brief OWDrawWidget::~OWDrawWidget
 */
OWDrawWidget::~OWDrawWidget()
{

}


/*!
 * \brief OWDrawWidget::GetMainCamera 위젯에 설정된 메인카메라를 가져오는 함수
 * \return
 */
MainCamera *OWDrawWidget::GetMainCamera()
{
    return this->m_mainCamera;
}


/*!
 * \brief OWDrawWidget::paintEvent 페인트 이벤트 함수
 */
void OWDrawWidget::paintEvent(QPaintEvent*)
{
    this->m_mainCamera->Draw(this, this->m_mousePoint);
}


/*!
 * \brief OWDrawWidget::resizeEvent 리사이즈 이벤트 함수
 * \param event
 */
void OWDrawWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    this->m_mainCamera->SetScreenSize(this->rect());
}


/*!
 * \brief OWDrawWidget::timerEvent 타이머 이벤트 함수
 * \param event
 */
void OWDrawWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

}


/*!
 * \brief OWDrawWidget::mousePressEvent 마우스 눌림 이벤트 함수
 * \param event
 */
void OWDrawWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

}


/*!
 * \brief OWDrawWidget::mouseReleaseEvent 마우스 눌림을 풀었을 때 함수
 * \param event
 */
void OWDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

}


/*!
 * \brief OWDrawWidget::mouseMoveEvent 마우스 이동 이벤트 함수
 * \param event
 */
void OWDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    *this->m_mousePoint = event->pos();
    update();

    QPoint metricLocation = GetMetricLocation(event->pos().x(), event->pos().y());
    int *borderData = this->GetMainCamera()->GetTileMap()->GetOutsideBorderLocation();
    if(borderData[TileMap::BORDER_TOP] == metricLocation.y()) {
        this->m_borderTouchDir = TileMap::BORDER_TOP;
    } else if(borderData[TileMap::BORDER_BOTTOM] == metricLocation.y()) {
        this->m_borderTouchDir = TileMap::BORDER_BOTTOM;
    } else if(borderData[TileMap::BORDER_LEFT] == metricLocation.x()) {
        this->m_borderTouchDir = TileMap::BORDER_LEFT;
    } else if(borderData[TileMap::BORDER_RIGHT] == metricLocation.x()) {
        this->m_borderTouchDir = TileMap::BORDER_RIGHT;
    } else {
        this->m_borderTouchDir = TileMap::BORDER_NONE;
    }
    this->GetMainCamera()->GetTileMap()->BorderTouchEvent(m_borderTouchDir);
}


/*!
 * \brief OWDrawWidget::SetBackgroundColor 메인카메라의 배경색을 지정하는 함수
 * \param color
 */
void OWDrawWidget::SetBackgroundColor(QColor color) {
    this->m_mainCamera->SetBackgroundColor(new QBrush(color));
    update();
}


/*!
 * \brief OWDrawWidget::GetMetricLocation 마우스 좌표에 해당하는 매트릭 좌표를 구하는 함수
 * \param mouseX
 * \param mouseY
 * \return
 */
QPoint OWDrawWidget::GetMetricLocation(int mouseX, int mouseY) {
    QPoint point = this->m_mainCamera->GetIsoMetric()->GetMetricLocation(mouseX, mouseY);
    return point;
}


/*!
 * \brief OWDrawWidget::GetBorderToucDir 위젯의 보더를 터치한 방향을 구하는 함수
 * \return
 */
int OWDrawWidget::GetBorderToucDir() {
    return this->m_borderTouchDir;
}


/*!
 * \brief OWDrawWidget::FadeIn 서서히 밝아지는 함수
 */
void OWDrawWidget::FadeIn()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}


/*!
 * \brief OWDrawWidget::FadeOut 서서히 어두어 지는 함수
 */
void OWDrawWidget::FadeOut()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this,SLOT(hideThisWidget()));
}
