/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
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
    this->m_mainCamera->OptionShowTileMap(true, true);

    this->m_mousePoint = new QPoint(100, 100);  // 시작 마우스 위치
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
    this->m_mainCamera->SetSize(this->rect());
}

void OWDrawWidget::timerEvent(QTimerEvent *event)
{

}

void OWDrawWidget::mousePressEvent(QMouseEvent *event)
{

}

void OWDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void OWDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    *this->m_mousePoint = event->pos();
    update();
}

void OWDrawWidget::SetBackgroundColor(QColor color) {
    this->m_mainCamera->SetBackgroundColor(new QBrush(color));
    update();
}

QPair<int, int> OWDrawWidget::GetMetricLocation(int mouseX, int mouseY) {
    QPair<int, int> pair = this->m_mainCamera->GetIsoMetric()->GetMetricLocation(mouseX, mouseY);
    return pair;
}
