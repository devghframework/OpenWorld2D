/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef OWDRAWWIDGET_H
#define OWDRAWWIDGET_H

#include "maincamera.h"

#include <QWidget>
#include <QPainter>

class OWDrawWidget : public QWidget
{
public:
    OWDrawWidget(QWidget* parent = nullptr);


protected:
  virtual void paintEvent(QPaintEvent*) override;
  virtual void resizeEvent(QResizeEvent*) override;
  virtual void timerEvent(QTimerEvent*) override;
  virtual void mousePressEvent(QMouseEvent*) override;
  virtual void mouseReleaseEvent(QMouseEvent*) override;
  virtual void mouseMoveEvent(QMouseEvent*) override;

public:
    void SetBackgroundColor(QColor);
    QPair<int, int> GetMetricLocation(int, int);

private:
    QWidget *m_openWorldWidget;
    MainCamera *m_mainCamera;
    QPoint *m_mousePoint;

public:
    MainCamera *GetMainCamera();
};

#endif // OWDRAWWIDGET_H
