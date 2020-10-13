// 10_MenuItem.cpp
#include <iostream>
using namespace std;

// 2. 함수 포인터 방식의 이벤트 처리
//   => 핸들러 기반 이벤트 처리

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



