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

#include "owdrawwidget.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QBrush>
#include <QColor>


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


OWDrawWidget::~OWDrawWidget()
{

}


MainCamera *OWDrawWidget::GetMainCamera()
{
    return this->m_mainCamera;
}


void OWDrawWidget::paintEvent(QPaintEvent*)
{
    this->m_mainCamera->Draw(this, this->m_mousePoint);
}


void OWDrawWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    this->m_mainCamera->SetScreenSize(this->rect());
}


void OWDrawWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

}


void OWDrawWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

}


void OWDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

}


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


void OWDrawWidget::SetBackgroundColor(QColor color) {
    this->m_mainCamera->SetBackgroundColor(new QBrush(color));
    update();
}


QPoint OWDrawWidget::GetMetricLocation(int mouseX, int mouseY) {
    QPoint point = this->m_mainCamera->GetIsoMetric()->GetMetricLocation(mouseX, mouseY);
    return point;
}


int OWDrawWidget::GetBorderToucDir() {
    return this->m_borderTouchDir;
}
