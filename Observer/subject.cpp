#include "observer/subject.h"

#include <QtCore>

Subject::Subject() {}

void Subject::AddObserver(IObserver *observer)
{
    Q_UNUSED(observer)
}
void Subject::RemoveObserver(IObserver *observer)
{
    Q_UNUSED(observer)
}
