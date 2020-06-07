/*!
    Copyright 2020. Coding Studio. All rights reserved.
    BSD License Usage

    [Coding Studio]
    Git     : https://github.com/devghframework/OpenWorld2D
    email   : devlee.freebsd@gmail.com
    twitch  : https://www.twitch.tv/codingstudio
    youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
*/

#ifndef MONITORING_H
#define MONITORING_H

#include "observer/iobserver.h"

class Monitoring : public IObserver
{

public:
    Monitoring();
    virtual ~Monitoring();

    void onNotify() override;
    void onMonitoring() override;

private:
    void Update();

    //    void monitoringObjectStatus(int);
    //    void monitoringAnimationNo(int);
    //    void monitoringDestinationArriveStatus(int);
    //    void monitoringObjectDirection(QString);
    //    void monitoringMetricLocation(QPoint);
    //    void monitoringMoveStartPoint(QPoint);
    //    void monitoringMoveEndPoint(QPoint);
    //    void monitoringMovePointPixel(QPoint);
    //    void monitoringMovePointPixelOld(QPoint);
    //    void monitoringMoveEndPointPixel(QPoint);
};

#endif // MONITORING_H
