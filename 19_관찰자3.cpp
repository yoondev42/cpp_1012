#include <vector>
#include <iostream>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

#include "IObserver.h"

class Subject {
    vector<IObserver*> v;
public:
    // virtual ~Subject() {}

    // C:\\Plugin 디렉토리에 약속된 DLL이 존재한다.
    // 1. DLL을 로드한다.
    // 2. DLL 안에서 CreateGraph 함수를 찾는다.
    // 3. CreateGraph를 호출해서 그래프 객체를 생성한다.
    // 4. 그래프 객체를 현재의 Subject의 attach 한다.

    Subject() {
        IoEnumFiles("C:\\Plugin", "*.dll", LoadModule, this);
    }

    static int LoadModule(string name, void* param) {
        cout << name << endl;

        void* addr = IoLoadModule(name);
        
        // IObserver* CreateGraph();
        typedef IObserver* (*FP)();
        FP f = static_cast<FP>(IoGetFunctionAddress(addr, "CreateGraph"));

        IObserver* p = f();

        Subject* self = static_cast<Subject*>(param);
        self->attach(p);

        return 1;
    }

    void attach(IObserver* p) {
        v.push_back(p);
        p->pSubject = this;
    }

    void detach(IObserver* p) {}

    void notify(void *p) {
        for (IObserver* e : v) {
            e->onUpdate(p);
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
        // const int* data = table->getData();
        // int len = table->getSize();

        int* data = (int*)d;
        int len = 5;

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
