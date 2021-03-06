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

#include <QMetaEnum>
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

public:
    template<typename T>
    /*!
     * \brief GetMetaEnum Enum 요소의 메타 이름을 가져온다.
     * \param value
     * \return 
     */
    static QString GetMetaEnum(const T value)
    {
        auto metaEnumMoveDir = QMetaEnum::fromType<T>();
        QString enumStr = metaEnumMoveDir.valueToKey(value);
        return enumStr;
    }

protected:
    /***********************************/
    /* 오브젝트의 액션이나 이벤트를 정의한다.    */
    /***********************************/

#pragma region OBJECT_ACTION

    virtual void CreateObject() = 0;
    virtual void DrawObject(QPainter *) = 0;
    virtual void MouseDown(int, int) = 0;
    virtual void MouseUp(int, int) = 0;
    virtual void MouseMove(int, int) = 0;
    virtual void MouseHover(int, int) = 0;

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
        STATUS_DONE,   // 프로세스가 모두 끝난 상태
        STATUS_STAY,   // 대기 상태
        STATUS_WORK,   // 걷는 상태
        STATUS_RUN,    // 달리는 상태
        STATUS_IDLE,   // 쉬는 상태
        STATUS_STOP,   // 액션을 하다 강제로 멈춘상태
        STATUS_TALK,   // 대화중
        STATUS_CHAT,   // 채팅중
        STATUS_ARRIVED // 목적지 도착
    };
    Q_ENUM(OBJECT_STATUS)

    /*!
     * \brief The OBJECT_MOVE_DIRECTION enum 사물이 움직이는 방향
     */
    enum OBJECT_MOVE_DIRECTION {
        DIR_NONE = 0b00000000, // 정면을 바라본 초기 상태
        DIR_N = 0b00000001,    // 1 북
        DIR_S = 0b00000010,    // 2 남
        DIR_E = 0b00000100,    // 4 동
        DIR_W = 0b00001000,    // 8 서
        DIR_SE = 0b00000110,   // 6 남동
        DIR_SW = 0b00001010,   // 10 남서
        DIR_NE = 0b00000101,   // 5 북동
        DIR_NW = 0b00001001,   // 9 북서
    };
    Q_ENUM(OBJECT_MOVE_DIRECTION)

    /*!
     * \brief The SPLITIMAGE_COPY_DIR enum 원본 이미지에서 복사할 방향
     */
    enum SPLITIMAGE_COPY_DIR { COPY_DIR_RIGHT = 0, COPY_DIR_DOWN };
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
    /*!
     * \brief actionNo 행동양식 번호 (OBJECT_STATUS)
     */
    int actionNo;

    /*!
     * \brief originFileName 이미지 원본 파일 이름
     */
    QString originFileName;

    /*!
     * \brief copyStartPoint 원본이미지에서 복사를 시작할 좌표
     */
    QPoint copyStartPoint;

    /*!
     * \brief copyDirection 복사할 방향 (SPLITIMAGE_COPY_DIR)
     */
    int copyDirection;

    /*!
     * \brief totalSplitCount 분할된 이미지 전체 갯수
     */
    int totalSplitCount;

    /*!
     * \brief fullWidth 이미지 전체 넓이
     */
    int fullWidth;

    /*!
     * \brief fullHeight 이미지 전체 높이
     */
    int fullHeight;

    /*!
     * \brief width 이미지 하나의 넓이
     */
    int width;

    /*!
     * \brief height 이미지 하나의 높이
     */
    int height;

    /*!
     * \brief movePixel 이동시 픽셀 (speed)
     */
    int movePixel;

    /*!
     * \brief bottom 바닥좌표
     */
    QPoint bottomLocation;

    /*!
     * \brief bottomGapFromMetricCenter
     */
    QPoint bottomGapFromMetricCenter;

    /*!
     * \brief splitImage 1차원 배열 (행동양식에 해당하는 이미지 배열)
     */
    QPixmap *splitImage;

} ObjectSplitImageInfo;

#endif // IOBJECTGENERATOR_H
