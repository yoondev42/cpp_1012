// 6_단위전략.cpp
#include <iostream>
using namespace std;

#if 0
template <typename T> class List {
public:
  void push_front(const T& a) {
    //...
  }
};

List<int> st;  // 전역 변수

int main() {
  st.push_front(10);
}
#endif

// 1. 동기화 여부를 인터페이스 기반의 다른 클래스로 분리하자.
//  장점: 정책을 실행시간에 교체할 수 있다.(setSync를 계속 호출할 수 있다.)
//  단점: 가상함수 기반이므로, 일반 함수에 비해 호출 부하가 있다.
//      - 인라인화가 불가능하다.
struct ISync {
  virtual ~ISync() {}

  virtual void Lock() = 0;
  virtual void UnLock() = 0;
};

template <typename T> class List {
  ISync* pSync;
public:
  void setSync(ISync* p) { pSync = p; }

  void push_front(const T& a) {
    pSync->Lock();
    //...
    pSync->UnLock();
  }
};

class MultiThread : public ISync {
public:
  void Lock() override {
    cout << "Mutex lock" << endl;
  }
  void UnLock() override {
    cout << "Mutex unlock" << endl;
  }
};

class SingleThread : public ISync {
public:
  void Lock() override {
  }
  void UnLock() override {
  }
};

List<int> st;

int main() {
  SingleThread lock1;
  MultiThread lock2;

  st.setSync(&lock1);
  st.push_front(10);     // Single Thread 모드로 동작합니다.

  st.setSync(&lock2);
  st.push_front(20);     // Multi Thread 모드로 동작합니다.
  


}



