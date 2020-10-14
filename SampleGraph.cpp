// SampleGraph.cpp

#include <iostream>
using namespace std;

#include "IObserver.h"

class SampleGraph : public IObserver {
public:
    void onUpdate(void* d) override {
        int* data = static_cast<int*>(d);
        int len = 5;

        cout << "************ Sample ************" << endl;
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