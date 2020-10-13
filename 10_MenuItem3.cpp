// 10_MenuItem.cpp
#include <iostream>
using namespace std;

// 2. 함수 포인터 방식의 이벤트 처리
//   => 핸들러 기반 이벤트 처리
//    C#: delegate라는 문법은 모든 타입의 함수를 담을 수 있는 객체
//  ObjC: selector라는 문법을 통해 모든 종류의 함수를 참조할 수 있다.
//   C++: 범용 함수 포인터가 존재하지 않는다.

// 아래 코드의 문제점
//  1. 아래의 MenuItem은 Dialog 객체만 사용할 수 있습니다.
//  2. 일반 함수는 사용할 수 없다.
//  => 범용 함수 포인터 타입을 설계해봅시다.

class Dialog;
class MenuItem {
  using HandlerType = void (Dialog::*)();

  // void (Dialog::*handler)();  // 멤버 함수포인터
  HandlerType handler;
  Dialog* object;             // 멤버 함수 포인터는 객체도 필요하다.
public:
  MenuItem() {}

  void setHandler(HandlerType h, Dialog* o) {
    handler = h;
    object = o;
  }

  virtual void command() {
    (object->*handler)();
  }
};

class Dialog {
public:
  void open() {
    cout << "Dialog open" << endl;
  }

  void close() {
    cout << "Dialog close" << endl;
  }
};

int main() {
  MenuItem m1;
  MenuItem m2;

  Dialog dlg;

  m1.setHandler(&Dialog::open, &dlg);
  m2.setHandler(&Dialog::close, &dlg);

  m1.command();
  m2.command();
}



