// 힙에 만드는 싱글톤
#include <iostream>
#include <mutex>
using namespace std;

#include <memory>

#if 0
class Sample {
public:
  Sample() { cout << "Sample" << endl; }
  ~Sample() { cout << "~Sample" << endl; }
};

void foo() {
  // Sample* p = new Sample;
  unique_ptr<Sample> p(new Sample);

  throw 1;  // 예외 발생

  // delete p;
}



int main() {
  try {
    foo();
  } catch (int& e) {
    printf("예외 발생: %d\n", e);
  }
  printf("main 종료\n");
}
#endif

class AutoLock {
  mutex& lock;
public:
  AutoLock(mutex& m) : lock(m) { lock.lock();   }
  ~AutoLock()                  { lock.unlock(); }
};


#if 1
class Cursor {
private:
  Cursor() {
    cout << "Cursor()" << endl;
  }
  Cursor(const Cursor&) = delete;
  Cursor& operator=(const Cursor&) = delete;

  static Cursor* sInstance;
  static mutex sMutex;
public:

  // new 연산은 예외 가능성이 있습니다.
  // => new 에서 예외가 발생할 경우, 데드락의 위험성이 있습니다.
  // => lock과 unlock을 직접 호출하지 않고, 생성자/소멸자를 이용해서 자동으로 처리될 수 있도록 만들어주는 것이 중요하다.
  //    RAII(Resource Acqusion Is Initilize) 라는 기술
  static Cursor& getInstance() {
    // sMutex.lock();
    AutoLock al(sMutex);
    if (sInstance == nullptr)
      sInstance = new Cursor;
    // sMutex.unlock();

    return *sInstance;
  }

#if 0
  // 아래의 코드는 2개이상의 스레드가 동시에 getInstance()를 호출할 경우
  // 문제가 발생할 수 있습니다.
  static Cursor& getInstance() {
    if (sInstance == nullptr)
      sInstance = new Cursor;

    return *sInstance;
  }
#endif
};

Cursor* Cursor::sInstance = nullptr;
mutex Cursor::sMutex;

int main() {
  auto& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  printf("%p %p\n", &c1, &c2);
}
#endif