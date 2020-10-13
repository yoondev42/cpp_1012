#include <iostream>
using namespace std;

// 핵심: 언어의 기능적인 부분이 제공되지 않을 경우,
//      해당 기능을 클래스로 래핑해서, 문제를 해결할 수 있다.
//      => 간접층의 원리
//         소프트웨어의 많은 문제를 간접층을 도입함으로써 해결 가능하다.

// 일반 함수와 모든 클래스의 멤버 함수를 보관하는 범용적 함수 포인터 타입을 만들어보자.
// => 새로운 클래스 타입을 만든다.

// 1. 일반 함수를 담을 수 있는 클래스 타입을 설계해보자.
//  일반 함수 포인터를 래핑한 클래스
class FunctionCommand {
  // void (*handler)();
  using HANDLER = void(*)();
  HANDLER handler;
public:
  FunctionCommand(HANDLER h) : handler(h) {}

  void execute() {
    handler();
  }
};


void foo() { cout << "foo" << endl; }



// 2. 모든 클래스의 멤버 함수를 담을 수 있는 클래스 타입을 설계해보자.
//  : 모든 타입의 멤버 함수를 참조하기 위해서는 템플릿 기반으로 설계되어야 한다.
template <typename T>
class MemberCommand {
  using HANDLER = void(T::*)();

  HANDLER handler;
  T* object;
public:
  MemberCommand(HANDLER h, T* obj) {
    handler = h;
    object = obj;
  }

  void execute() {
    (object->*handler)();
  }
};

class Dialog {
public:
  void open() { cout << "Dialog open" << endl; }
};

class Window {
public:
  void show() { cout << "Window show" << endl; }
};

int main() {
  Dialog dlg;
  MemberCommand<Dialog> fp1(&Dialog::open, &dlg);

  Window window;
  MemberCommand<Window> fp2(&Window::show, &window);

  fp1.execute();
  fp2.execute();

  // FunctionCommand fp(&foo);
  // fp.execute();
}


// 3. 위의 두 개의 타입을 공통의 부모로 묶는다.