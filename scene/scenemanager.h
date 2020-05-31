/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

#include <QObject>
#include <QPaintEvent>
#include <QTimer>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPoint>

#include <coordinatesystem/isometric.h>
#include <camera/maincamera.h>


class SceneManager : public QObject
{
    Q_OBJECT

public:
    SceneManager(Isometric *);
    virtual ~SceneManager();

    Scene *GetScene(QString &);
    void SceneAction();
    void SceneStop();
    void SetCamera(const MainCamera &);

    void paintEvent(const QPaintEvent *);
    void resizeEvent(const QResizeEvent *);
    void mousePressEvent(const QMouseEvent *);
    void mouseReleaseEvent(const QMouseEvent *);
    void mouseMoveEvent(const QMouseEvent *);

protected:
    void CreateScene();

private slots:
    void SceneWork();

private:
    QTimer timer; // 삭제 예정
    //MainCamera m_mainCamera;
    Isometric *m_isometric;
    QPoint point;

private:
#pragma region SCENE_FIELDS

    Scene *m_defaultScene;

#pragma endregion SCENE_FIELDS
};

#endif // SCENEMANAGER_H
