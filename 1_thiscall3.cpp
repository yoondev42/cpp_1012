#include <iostream>
using namespace std;

// 멤버 함수와 함수 포인터
class Dialog {
public:
  void Close() { cout << "Dialog::Close" << endl; }

  // 정적 멤버 함수는 일반 함수 포인터를 이용해서 호출하는 것이 가능합니다.
  static void goo() {
    cout << "Dialog::goo" << endl;
  }
};

void foo() {
  cout << "foo" << endl;
}

int main() {
  void (*f4)() = &Dialog::goo;
  (*f4)();


  // 멤버 함수의 주소를 담는 방법
  // => 멤버 함수 포인터
  void (Dialog::*f3)() = &Dialog::Close;
  
  // 멤버 함수 포인터를 통해 멤버 함수를 호출하기 위해서는 객체가 반드시 필요하다.
  Dialog dialog;
  (dialog.*f3)();

  Dialog* p = new Dialog;
  (p->*f3)();
  //-----------------

  void (*f1)() = &foo;
  (*f1)();
  // 함수의 이름은 함수의 주소로 해석된다 - Decay
  void (*f2)() = foo;
  f2();
}