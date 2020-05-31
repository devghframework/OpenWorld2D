/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#ifndef IOBJECTGENERATOR_H
#define IOBJECTGENERATOR_H

#include <QObject>
#include <QPainter>

/*!
 * \class IObjectGenerator
 * \brief The IObjectGenerator class 객체 생성자 인터페이스 클레스
 * 객체의 행동양식과 행동양식을 정의한다.
 *
 * 오브젝트 카테고리 설정 예)
 * -------------------------------------------------------------
 * OWObject
 * -------------------------------------------------------------
 * 케릭터                          || 사물
 * -------------------------------------------------------------
 * 플레이어 | 강아지 | 고양이 | 물고기   ||  바닥 | 도로 | 건물 | 나무
 * -------------------------------------------------------------
 * 프로토스   진도개                     바닥1   도로1  건물1  나무1
 * 테란      웰시코기                    바닥2   도로2  건물2  나무2
 * 저그
 * -------------------------------------------------------------
 */
class IOwObject
{
    Q_GADGET
    //Q_OBJECT

protected:

    // 오브젝트의 액션이나 이벤트를 정의한다.
    #pragma region OBJECT_ACTION

    //virtual QMap<QString, QObject> GetObjects() = 0;
    //virtual QObject *GetObject(QString key) = 0;
    virtual void CreateObject() {}
    virtual void DrawObject(QPainter *) {}
    virtual void MouseDown(int, int) {}
    virtual void MouseUp(int, int) {}
    virtual void MouseMove(int, int) {}

#pragma endregion OBJECT_ACTION

public:
    /*!
     * \brief The MOUSE_ACTION enum 마우스 이벤트
     */
    enum MOUSE_ACTION {
        MOUSE_DEFAULT = 0,
        MOUSE_HOVER,
        MOUSE_CLICk
    };
    Q_ENUM(MOUSE_ACTION)

    /*!
     * \brief The OBJECT_STATUS enum 오브젝트의 상태
     */
    enum OBJECT_STATUS {
        STATUS_NONE = 0, // 초기상태 (일반 사물일 경우 NONE 값을 가진다. 나무, 돌 등)
        STATUS_STAY, // 대기 상태
        STATUS_WORK, // 걷는 상태
        STATUS_RUN,  // 달리는 상태
        STATUS_IDLE, // 쉬는 상태
        STATUS_STOP, // 액션을 하다 멈춘상태
        STATUS_TALK, // 대화중
        STATUS_CHAT  // 채팅중
    };
    Q_ENUM(OBJECT_STATUS)

    /*!
     * \brief The OBJECT_MOVE_DIRECTION enum 사물이 움직이는 방향
     */
    enum OBJECT_MOVE_DIRECTION {
        DIRECTION_DEFAULT = 0, // 정면을 바라본 초기 상태
        DIRECTION_E,           // 동쪽
        DIRECTION_W,           // 서쪽
        DIRECTION_S,           // 남쪽
        DIRECTION_N,           // 북쪽
        DIRECTION_NE,          // 북동쪽
        DIRECTION_NW,          // 북서쪽
        DIRECTION_SE,          // 남동쪽
        DIRECTION_SW           // 남서쪽
    };
    Q_ENUM(OBJECT_MOVE_DIRECTION)

    /*!
     * \brief The SPLITIMAGE_COPY_DIR enum 원본 이미지에서 복사할 방향
     */
    enum SPLITIMAGE_COPY_DIR { COPY_RIGHT = 0, COPY_BOTTOM };
    Q_ENUM(SPLITIMAGE_COPY_DIR)

    /*!
     * \brief The OBJECT_DESTINATION enum 목작지 도착지 여부 (출발, 도착)
     */
    enum OBJECT_DESTINATION { NO_DESTINATION = 0, DESTINATION_START, DESTINATION_ARRIVED };
    Q_ENUM(OBJECT_DESTINATION)
};

/*!
 * \brief The structObjectSplitImage struct Split image 정보
 * TODO : C/S 구성시 전송할 수 있도록 Serialization 시켜야 한다.
 */
typedef struct structObjectSplitImage {
    int actionNo;           // 행동양식 번호 (ex: 0: 달리기, 1: 걷기, 2: 뛰기, 3: 쉬기 등)
    QString originFileName; // 이미지 원본 파일 이름
    QPoint copyStartPoint;  // 원본이미지에서 복사를 시작할 좌표
    int copyDirection;      // 복사할 방향 (SPLITIMAGE_COPY_DIR)
    int totalSplitCount;    // 분할된 이미지 전체 갯수
    int fullWidth;          // 이미지 전체 넓이
    int fullHeight;         // 이미지 전체 높이
    int width;              // 이미지 하나의 넓이
    int height;             // 이미지 하나의 높이
    int movePixel;          // 이동시 픽셀
    QPixmap *splitImage;    // 1차원 배열 (행동양식에 해당하는 이미지 배열)
} ObjectSplitImageInfo;

#endif // IOBJECTGENERATOR_H
