

#include <iostream>
using namespace std;

// Template 기반의 정책 교체 - C++ idioms
// 장점: 정책이 템플릿 인자로 컴파일 타임에 결정된다.
//      가상함수이므로, 함수의 호출이 인라인화가 가능하다.
//      빠르다!
// 단점: 실행 시간에 정책 교체가 불가능하다.
//  => 단위 전략(Policy based design)
//     : 정책을 담은 코드를 컴파일 시간에 생성해 내는 기술
//       Modern C++ Design

template <typename T, typename ThreadModel>
class List {
  ThreadModel lock;
public:
  void push_front(const T& a) {
    lock.Lock();
    // ...
    lock.Unlock();
  }
};

class SingleThread {
public:
  inline void Lock() {

  }
  inline void Unlock() {

  }
};

class MultiThread {
public:
  inline void Lock() {
    cout << "Mutex lock" << endl;
  }
  inline void Unlock() {
    cout << "Mutex unlock" << endl;
  }
};


List<int, SingleThread> st;
// List<int, MultiThread> st;

int main() {
  st.push_front(10);
}