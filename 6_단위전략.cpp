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



