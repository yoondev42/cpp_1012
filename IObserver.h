// IObserver.h
#ifndef IOBSERVER_H
#define IOBSERVER_H

class Subject;
struct IObserver {
    virtual ~IObserver() {}

    Subject* pSubject;
    virtual void onUpdate(void* data) = 0;
};

#endif