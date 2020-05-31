/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef OWOBJECT_H
#define OWOBJECT_H

#include "factory/iowobject.h"

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QTimer>

/*!
 * \class OwObject
 * \brief The OwObject class
 *
 */
class OwObject : public IOwObject
{
    //Q_OBJECT

public:
    OwObject();
    virtual ~OwObject();

    QMap<QString, QObject> GetObjects() override;
    QObject *GetObject(QString key) override;
    void CreateObject() override;
    void DrawObject(QPainter *painter) override;

    void MouseDown(int metricX, int metricY) override;
    void MouseUp(int metricX, int metricY) override;
    void MouseMove(int metricX, int metricY) override;

    void SetObjectSplitImageInfo(ObjectSplitImageInfo *);
    ObjectSplitImageInfo *GetObjectSplitImageInfo();

private:
    void CreateSplitImage();

//private slots:
//    void ObjectAction();

private:
//    QTimer actionTimer;

private:
// 객체의 기본 특성을 정의한다.
#pragma region OBJECT_FIELDS

    /*!
     * \brief m_splitObjectInfo
     * 하나의 객체는 여러 행동 양식을 가질 수 있다.
     * 하나의 행동양식은 여러장의 이미지로 이루어 진다.
     * 각 배열에는 하나의 행동양식으로 이루어져 있다.
     */
    ObjectSplitImageInfo *m_splitObjectInfo; // 객체의 행동 이미지가 들어 있는 구조체의 1차원 배열
    //int m_objectStatus;    // 오브젝트 상태 (OBJECT_STATUS 값을 가진다.)
    //int m_animationNo = 0; // Animation 을 할 경우 split image 의 번호

    QPoint m_metricLocation; // 오브젝트의 매트릭 좌표
    QPoint m_pixelLocation;  // 오브젝트의 픽셀 좌표

    int m_objectStatus;  // OBJECT_STATUS

    QPoint m_moveStartPoint; // 시작좌표 : 케릭터 이동
    QPoint m_moveEndPoint;   // 도착좌표 : 케릭터 이동

#pragma endregion OBJECT_FIELDS
};

#endif // OWOBJECT_H
