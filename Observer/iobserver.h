#ifndef IOBSERVER_H
#define IOBSERVER_H


class IObserver
{
public:
    virtual ~IObserver(){};

    virtual void onNotify() = 0;
    virtual void onMonitoring() = 0;
};

#endif // IOBSERVER_H
