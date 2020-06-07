#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer/iobserver.h"

class Subject
{
public:
    Subject();

    void AddObserver(IObserver *observer);
    void RemoveObserver(IObserver *observer);
};

#endif // SUBJECT_H
