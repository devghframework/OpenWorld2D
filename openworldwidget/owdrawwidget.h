/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef OWDRAWWIDGET_H
#define OWDRAWWIDGET_H

#include "camera/maincamera.h"

#include <scene/scene.h>
#include <scene/scenemanager.h>

#include <QPainter>
#include <QThread>
#include <QWidget>

/*!
 * \class OWDrawWidget
 * \brief The OWDrawWidget class
 *
 * 오픈월드 메인 위젯
 */
class OWDrawWidget : public QWidget
{
    //QGraphicsView -- 참고
public:
    OWDrawWidget(QWidget *parent = nullptr);
    ~OWDrawWidget();

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;
    virtual void timerEvent(QTimerEvent *) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;

public:
    void SetBackgroundColor(QColor);
    Isometric *GetIsometric();
    QPoint GetMetricLocation(int, int);
    int GetBorderToucDir();
    void FadeIn();
    void FadeOut();
    SceneManager *GetSceneManager();

private:
    QWidget *m_openWorldWidget;
    Isometric *m_isometric;
    SceneManager *m_sceneManager;
    MainCamera *m_mainCamera;
    QPoint *m_mousePoint;

private:
    QTimer m_renderingTimer;

    /*!
     * \brief m_borderTouchDir 마우스가 어느방향의 테두리를 터치하였는지 저장
     */
    int m_borderTouchDir = TileMap::BORDER_NONE;


public:
    MainCamera *GetMainCamera();
};

#endif // OWDRAWWIDGET_H
