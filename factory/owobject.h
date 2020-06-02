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

#include <QMap>
#include <QObject>
#include <QPaintEvent>
#include <QPoint>
#include <QSize>
#include <QTimer>

#include <coordinatesystem/isometric.h>

/*!
 * \class OwObject
 * \brief The OwObject class 오브젝트 클래스 (케릭터 성질과 움직임을 처리한다.)
 *
 */
class OwObject : public QObject, IOwObject
{
    Q_OBJECT
    //Q_DISABLE_COPY(OwObject)

public:
    OwObject(Isometric *isometric);
    virtual ~OwObject();

    void CreateObject() override;
    void DrawObject(QPainter *painter) override;
    void MouseDown(int metricX, int metricY) override;
    void MouseUp(int metricX, int metricY) override;
    void MouseMove(int metricX, int metricY) override;
    void MouseHover(int metricX, int metricY) override;

    /*!
     * \brief SetObjectSplitImageInfo 오브젝트의 움직임 애니메이션 이미지를 원본이미지에서 복사하는 함수
     */
    void SetObjectSplitImageInfo(QMap<QString, ObjectSplitImageInfo *>);

    /****************************************/
    /* 객체의 현재 상태                         */
    /****************************************/
    int GetObjectStatus();
    int GetAnimationNo();
    int GetDestinationArriveStatus();
    QPoint GetMetricLocation();
    QPoint GetPixelLocation();
    QPoint GetMoveStartPoint();
    QPoint GetMoveEndPoint();
    QPoint GetMovePointPixel();
    QPoint GetMovePointPixelOld();
    QPoint GetMoveEndPointPixel();
    /****************************************/

private:
    /*!
     * \brief CreateSplitImage 저장된 정보로 원본 이미지에서 분할하여 배열 이미지로 복사한다.
     */
    void CreateSplitImage();

    /*!
     * \brief GetDirection 오브젝트가 움직이는 방향을 계산한다.
     * \param moveOldX
     * \param moveOldY
     * \param moveX
     * \param moveY
     */
    void GetDirection(int moveOldX, int moveOldY, int moveX, int moveY);

private slots:
    /*!
     * \brief ObjectAction 오브젝트 움직임 계산 함수 (m_actionTimer에 의해 호출된다.)
     */
    void ObjectAction();

private:
    /*!
     * \brief m_isometric 좌표계산용 매트릭 클래스
     */
    Isometric *m_isometric;

    /*!
     * \brief m_actionTimer 액션 렌더링 타이머
     */
    QTimer m_actionTimer;

public:
    /*!
     * \brief m_splitObjectInfo 객체의 행동 이미지가 들어 있는 구조체의 1차원 배열
     */
    QMap<QString, ObjectSplitImageInfo *> m_splitObjectInfo;

private:
    /*************************/
    /* 객체의 기본 특성을 정의한다. */
    /*************************/

#pragma region OBJECT_FIELDS

    /*!
     * \brief m_splitObjectInfo 오브젝트 상태 (OBJECT_STATUS 값을 가진다.)
     * 하나의 객체는 여러 행동 양식을 가질 수 있다.
     * 하나의 행동양식은 여러장의 이미지로 이루어 진다.
     * 각 배열에는 하나의 행동양식으로 이루어져 있다.
     */
    int m_objectStatus;

    /*!
     * \brief m_animationNo Animation 을 할 경우 split image 의 번호
     */
    int m_animationNo = 0;

    /*!
     * \brief m_destination 목적지 도착상태
     */
    int m_destinationArriveStatus = OBJECT_DESTINATION::NO_DESTINATION;

    /*!
     * \brief m_metricLocation 오브젝트의 매트릭 좌표
     */
    QPoint m_metricLocation;

    /*!
     * \brief m_pixelLocation 오브젝트의 픽셀 좌표
     */
    QPoint m_pixelLocation;

    /*!
     * \brief m_moveStartPoint 시작좌표 : 케릭터 이동
     */
    QPoint m_moveStartPoint;

    /*!
     * \brief m_moveEndPoint 도착좌표 : 케릭터 이동
     */
    QPoint m_moveEndPoint;

    /*!
     * \brief m_movePointPixel 시작좌표 : 케릭터 이동
     */
    QPoint m_movePointPixel;

    /*!
     * \brief m_movePointPixelOld 시작좌표 : 케릭터 이동
     */
    QPoint m_movePointPixelOld;

    /*!
     * \brief m_moveEndPointPixel 도착좌표 : 케릭터 이동
     */
    QPoint m_moveEndPointPixel;

    /*!
     * \brief m_objectBottomLocationPixel 오브젝트가 서 있는 좌표
     */
    QPoint m_objectBottomLocationPixel;

    /*!
     * \brief m_actionName 행동 명칭
     */
    QString m_actionName;

#pragma endregion OBJECT_FIELDS
};

#endif // OWOBJECT_H
