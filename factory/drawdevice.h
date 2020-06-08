#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include <QObject>
#include <QPainter>

class DrawDevice
{
public:
    DrawDevice();
    virtual ~DrawDevice();

    void Update(QObject *, QPainter &);
};

#endif // DRAWDEVICE_H
