/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "factory/owobject.h"

#include <QString>
#include <QImageReader>
#include <QPainter>
#include <QMessageBox>
#include <QMap>
#include <QDebug>
#include <QThread>


OwObject::OwObject()
    : IOwObject()
{
    this->m_objectStatus = IOwObject::NONE;

    //connect(&actionTimer, SIGNAL (timeout()), this, SLOT (ObjectAction()));
}

OwObject::~OwObject()
{

}

//void OwObject::ObjectAction()
//{

//}


QMap<QString, QObject> OwObject::GetObjects()
{
    QMap<QString, QObject> empty;
    return empty;
}

QObject *OwObject::GetObject(QString key)
{
    Q_UNUSED(key);

    QObject *obj = new QObject();
    return obj;
}

void OwObject::CreateObject() {

}

void OwObject::DrawObject(QPainter *painter)
{
    painter->drawPixmap(100, 100, this->m_splitObjectInfo->splitImage[0]);
}

void OwObject::MouseDown(int metricX, int metricY)
{
    qDebug() << "Metric Location(X,Y) : " << QString::number(metricX) << ", "
             << QString::number(metricY);
    qDebug() << "Object Status: " << this->m_objectStatus;

    if (this->m_objectStatus == IOwObject::NONE) {
        this->m_objectStatus = IOwObject::WORK;

        this->m_moveStartPoint.setX(metricX);
        this->m_moveStartPoint.setY(metricY);
    } else if (this->m_objectStatus == IOwObject::WORK) {
        this->m_moveEndPoint.setX(metricX);
        this->m_moveEndPoint.setY(metricY);

        // 걷기 시작한다.
        // 1.길찾기 알고리즘
        // 2.걷는 에니메이션 출력 (쓰레드 처리를 해야 하는데....)
        qDebug() << "걷는다...."
                 << "도착할 때까지...";
        // 쓰레드 만들자....
        // 일단 테스트
        do {
            if (this->m_moveEndPoint.x() > this->m_moveStartPoint.x()) {
                this->m_moveStartPoint.setX(this->m_moveStartPoint.x() + 1);
            } else if (this->m_moveEndPoint.x() < this->m_moveStartPoint.x()) {
                this->m_moveStartPoint.setX(this->m_moveStartPoint.x() - 1);
            } else {
                qDebug() << "X 도착.";
            }

            if (this->m_moveEndPoint.y() > this->m_moveStartPoint.y()) {
                this->m_moveStartPoint.setY(this->m_moveStartPoint.y() + 1);
            } else if (this->m_moveEndPoint.y() < this->m_moveStartPoint.y()) {
                this->m_moveStartPoint.setY(this->m_moveStartPoint.y() - 1);
            } else {
                qDebug() << "Y 도착.";
            }
            qDebug() << "MOVING Start(x,y) : " << this->m_moveStartPoint.x() << ", "
                     << this->m_moveStartPoint.y() << " >> End(x,y) : " << this->m_moveEndPoint.x()
                     << ", " << this->m_moveEndPoint.y();

        } while (this->m_moveStartPoint.x() != this->m_moveEndPoint.x()
                 || this->m_moveStartPoint.y() != this->m_moveEndPoint.y());

        qDebug(">>>> 도착함.....");

        this->m_objectStatus = IOwObject::NONE;
    }
}

void OwObject::MouseUp(int metricX, int metricY)
{
    Q_UNUSED(metricX);
    Q_UNUSED(metricY);
}

void OwObject::MouseMove(int metricX, int metricY)
{
    Q_UNUSED(metricX);
    Q_UNUSED(metricY);
}

void OwObject::SetObjectSplitImageInfo(ObjectSplitImageInfo *objInfo)
{
    this->m_splitObjectInfo = objInfo;
    CreateSplitImage();
}

ObjectSplitImageInfo *OwObject::GetObjectSplitImageInfo()
{
    return this->m_splitObjectInfo;
}

void OwObject::CreateSplitImage()
{
    QString fileName = this->m_splitObjectInfo->originFileName;
    QImageReader r(fileName);

    QImage i = r.read();
    if (!i.isNull()) {
        QPixmap pixmap;
        pixmap = QPixmap::fromImage(i);

        this->m_splitObjectInfo->splitImage = new QPixmap[this->m_splitObjectInfo->totalSplitCount];

        switch (this->m_splitObjectInfo->copyDirection) {
            case IOwObject::RIGHT: {
                int x = this->m_splitObjectInfo->copyStartPoint.x();
                int y = this->m_splitObjectInfo->copyStartPoint.y();
                for (int idx = 0; idx < this->m_splitObjectInfo->totalSplitCount; idx++) {
                    this->m_splitObjectInfo->splitImage[idx]
                        = pixmap.copy(x,
                                      y,
                                      this->m_splitObjectInfo->width,
                                      this->m_splitObjectInfo->height);
                    x += this->m_splitObjectInfo->width;
                }
                break;
            }
            case IOwObject::BOTTOM: {
                int x = this->m_splitObjectInfo->copyStartPoint.x();
                int y = this->m_splitObjectInfo->copyStartPoint.y();
                for (int idx = 0; idx < this->m_splitObjectInfo->totalSplitCount; idx++) {
                    this->m_splitObjectInfo->splitImage[idx]
                        = pixmap.copy(x,
                                      y,
                                      this->m_splitObjectInfo->width,
                                      this->m_splitObjectInfo->height);
                    y += this->m_splitObjectInfo->height;
                }
                break;
            }
            default: {
                QMessageBox msgBox;
                msgBox.setText("복사할 방향을 지정하지 않았습니다.");
                msgBox.setInformativeText(
                    "원본이미지에서 복사할 방향을 지정해 주십시오.\r\n(RIGHT 또는 BOTTOM)");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.exec();
                break;
            }
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("이미지 파일을 읽을 수 없습니다.");
        msgBox.setInformativeText(
            "이미지 파일 위치와 이미지 포멧을 확인해 주십시오.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

}
