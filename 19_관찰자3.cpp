#include <vector>
#include <iostream>
using namespace std;

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

class Subject {
    vector<IObserver*> v;
public:
    virtual ~Subject() {}

    void attach(IObserver* p) {
        v.push_back(p);
        p->pSubject = this;
    }

    void detach(IObserver* p) {}

    void notify(void *p) {
        for (IObserver* p : v) {
            p->onUpdate(p);
        }
    }
};

class Table : public Subject {
    int data[5];
public:
    Table() { memset(data, 0, sizeof data); }

    const int* getData() const { return data; }
    int getSize() const { return 5; }

    void edit() {
        while (1) {
            int index;
            cout << "index: ";  cin >> index;
            cout << "data: "; cin >> data[index];

            notify(data);
        }
    }
};

//---------
class PieGraph : public IObserver {
public:
    void onUpdate(void* d) override {
        Table* table = static_cast<Table*>(pSubject);
        const int* data = table->getData();
        int len = table->getSize();

        cout << "************ Pie ************" << endl;
        for (int i = 0; i < len; ++i)
            cout << i << ": " << data[i] << endl;
    }
};

class BarGraph : public IObserver {
public:
    void onUpdate(void* d) override {
        Table* table = static_cast<Table*>(pSubject);
        const int* data = table->getData();
        int len = table->getSize();

        cout << "************ Bar ************" << endl;
        for (int i = 0; i < len; ++i)
            cout << i << ": " << data[i] << endl;
    }
};

int main() {
    Table table;
    PieGraph pg;
    BarGraph bg;

    table.attach(&pg);
    table.attach(&bg);

    table.edit();
}


//....
// SampleGraph.cpp

#include <iostream>
using namespace std;

#include "IObserver.h"

class SampleGraph : public IObserver {
public:
    void onUpdate(void* d) override {
        int* data = static_cast<int*>(d);
        int len = 5;

        cout << "************ Pie ************" << endl;
        for (int i = 0; i < len; ++i)
            cout << i << ": " << data[i] << endl;
    }
};

// SampleGraph.dll
// SampleGraph라는 이름은 현재 DLL을 만드는 사람만 알고 있습니다.
// .DLL내부에서 자신이 만든 클래스의 객체를 생성해주어야 합니다.
//  "함수를 하나 약속합니다"

extern "C"
__declspec(dllexport)
IObserver* CreateGraph() {
    return new SampleGraph;
}

// cl SampleGraph.cpp /LD