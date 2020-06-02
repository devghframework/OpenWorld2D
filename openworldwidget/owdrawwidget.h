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
 * \brief The OWDrawWidget class 오플월드 메인 위젯
 * 
 * 하위 오브젝트들간 데이타 연동이 필요할 경우 현재 오브젝트의 함수를 통해 데이타를 공유하도록 한다.
 */
class OWDrawWidget : public QWidget
{
public:
    const static int RENDERING_TIME = 50; //millisecond

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
    int GetBorderTouchDir();
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
