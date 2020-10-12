// C++의 많은 라이브러리는 C언어로 사용하던 많은 기술을 클래스 기반으로 캡슐화해서 사용합니다.
//  => 'Thread', Window, Timer

#include <iostream>
using namespace std;

// Windows
// #include <Windows.h>
//    - CreateThread

// Unix(Linux / macOS)
#include <pthread.h>
//    - pthread_create


class Thread {
public:
  virtual bool threadLoop() {
    return false;
  }

  // 1. 아래 함수가 정적 멤버 함수일 수 밖에 없는 이유를 정확히 알아야 합니다
  //    : 정적 멤버 함수는 일반 함수의 시그니처와 동일하다.
  //      일반 함수 포인터를 정적 멤버 함수를 가르키는 용도로 사용할 수 있다.
  // 2. 정적 멤버 함수에서 멤버 함수를 호출하는 것이 불가능하다.
  //    : this가 존재하지 않기 때문입니다.
  // static DWORD __stdcall _threadLoop(void* p) {} 
  // 3. this가 없으므로, this를 명시적으로 전달하는 기술
  static void* _threadLoop(void* p) {
    // threadLoop();  // ?

    // 1. 전달받은 p를 Thread 타입으로 변환합니다.
    Thread* self = static_cast<Thread*>(p);
    // 2. self를 통해 멤버 데이터 또는 멤버 함수를 호출할 수 있습니다.
    self->threadLoop();

    return 0;
  }

  void run() {
    pthread_t thread;
    pthread_create(&thread, 0, &_threadLoop, this);

    // CreateThread(0, 0, &_threadLoop, this, 0, 0);
  }

};

//-----------------------
class MyThread : public Thread {
public:
  bool threadLoop() override {
    cout << "MyThread threadLoop" << endl;
    return true;
  }
};

int main() {
  MyThread t;
  t.run();        // 이 순간 스레드가 생성되어서, 가상함수인 threadLoop()를 수행해야 합니다.

  getchar();
}





#if 0
// Windows
#if 0
DWORD __stdcall foo(void* p) {
  printf("%s\n", p);
  return 0;
}
#endif
// Linux
void* foo(void* p) {
  printf("%s\n", p);
  return 0;
}

int main() {
  // Windows
  // CreateThread(0, 0, foo, (void*)"A", 0, 0);
  pthread_t thread;
  pthread_create(&thread, 0, foo, (void*)"A");

  getchar();
}
#endif