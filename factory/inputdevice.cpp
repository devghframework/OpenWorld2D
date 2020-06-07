#include "factory/inputdevice.h"
#include "factory/owobject.h"

InputDevice::InputDevice() {}
InputDevice::~InputDevice() {}

void InputDevice::Update(QObject *qobject, Isometric &isometric)
{
    OwObject *object = qobject_cast<OwObject *>(qobject);

    // 목적지에 도착하였을 경우 움직임 처리
    if (object->GetObjectStatus() == IOwObject::STATUS_ARRIVED) {
        if (object->GetAnimationNo()
            >= (object->GetSplitObjectInfo(object->GetActionName())->totalSplitCount - 1)) {
            object->SetObjectStatus(IOwObject::STATUS_DONE);
        }
    }

    // 모든 처리가 완료 되었을 경우 처리
    else if (object->GetObjectStatus() == IOwObject::STATUS_DONE) {
        object->ActionTimerStop();
        object->SetActionName(IOwObject::GetMetaEnum(IOwObject::OBJECT_MOVE_DIRECTION::DIR_S));
        object->SetObjectStatus(IOwObject::STATUS_NONE);
        object->InitAnimation();
    }

    // 움직임 처리
    else {
        // 방향을 찾는다.
        object->GetDirection(object->GetMovePointPixelOld().x(),
                             object->GetMovePointPixelOld().y(),
                             object->GetMovePointPixel().x(),
                             object->GetMovePointPixel().y());

        // 아무것 안하는 상태일 경우 DIRECTION_S 방향을 보도록 한다.
        if (object->GetActionName()
            == IOwObject::GetMetaEnum(IOwObject::OBJECT_MOVE_DIRECTION::DIR_NONE)) {
            object->SetActionName(IOwObject::GetMetaEnum(IOwObject::OBJECT_MOVE_DIRECTION::DIR_S));
        }

        // 현재 좌표를 이전좌표로 백업한다.
        object->SetMovePointPixelOld(object->GetMovePointPixel());

        int x = object->GetMovePointPixel().x();
        int y = object->GetMovePointPixel().y();

        // 현재 좌표가 목적지 보다 좌측에 있을 경우
        if (object->GetMoveEndPointPixel().x() > object->GetMovePointPixel().x()) {
            x += object->GetSplitObjectInfo(object->GetActionName())->movePixel;
        }

        // 현재 좌표가 목적지 보다 우측에 있을 경우
        else if (object->GetMoveEndPoint().x() < object->GetMovePointPixel().x()) {
            x -= object->GetSplitObjectInfo(object->GetActionName())->movePixel;
        }

        // 현재 좌표가 목적지 보다 아래에 있을 경우
        if (object->GetMoveEndPointPixel().y() > object->GetMovePointPixel().y()) {
            y += object->GetSplitObjectInfo(object->GetActionName())->movePixel;
        }

        // 현재 좌표가 목적지 보다 위에 있을 경우
        else if (object->GetMoveEndPointPixel().y() < object->GetMovePointPixel().y()) {
            y -= object->GetSplitObjectInfo(object->GetActionName())->movePixel;
        }

        QPoint point(x, y);
        object->SetMovePointPixel(point);

        // 현재 좌표가 목적지와 같을 경우
        if (object->GetMovePointPixel().x() == object->GetMoveEndPointPixel().x()
            && object->GetMovePointPixel().y() == object->GetMoveEndPointPixel().y()) {
            // 현재 상태를 목적지 도착으로 변경하고 목적지 도착 행동을 하도록 설정한다.
            object->SetDestinationArriveStatus(IOwObject::DESTINATION_ARRIVED);
            object->SetObjectStatus(IOwObject::STATUS_ARRIVED);
            object->SetActionName(IOwObject::GetMetaEnum(IOwObject::OBJECT_STATUS::STATUS_ARRIVED));
            object->InitAnimation();
        }
    }

    int bottomX = object->GetMovePointPixel().x() + isometric.defaultIsometricHarfWidth();
    int bottomY = object->GetMoveEndPoint().y() + isometric.defaultIsometricHarfHeight();
    QPoint bottomPoint(bottomX, bottomY);
    object->SetObjectBottomLocationPixel(bottomPoint);

    if (object->GetObjectBottomLocationPixel().x() >= 0
        && object->GetObjectBottomLocationPixel().y() >= 0) {
        object->SetMetricLocation(
            isometric.GetMetricLocation(object->GetObjectBottomLocationPixel().x(),
                                        object->GetObjectBottomLocationPixel().y()));
    }

    // 모니터링
    //    Main->monitoringObjectStatus(object.GetActionName());
    //    Main->monitoringAnimationNo(this->m_animationNo);
    //    Main->monitoringDestinationArriveStatus(this->m_destinationArriveStatus);
    //    Main->monitoringObjectDirection(this->m_actionName);
    //    Main->monitoringMetricLocation(this->m_metricLocation);
    //    Main->monitoringMovePointPixel(this->m_movePointPixel);
    //    Main->monitoringMoveStartPoint(this->m_moveStartPoint);
    //    Main->monitoringMoveEndPoint(this->m_moveEndPoint);
    //    Main->monitoringMovePointPixelOld(this->m_movePointPixelOld);
    //    Main->monitoringMoveEndPointPixel(this->m_moveEndPointPixel);
}
