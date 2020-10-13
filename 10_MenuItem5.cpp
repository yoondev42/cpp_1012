
#include <iostream>
using namespace std;

// STL에는 범용 함수 포인터 클래스가 타입이 존재합니다.
#include <functional>

class Window {
public:
  void show() { cout << "Window show" << endl; }
};

class Dialog {
public:
  // void open(Dialog* this = dlg)
  void open() { cout << "Dialog open" << endl; }
};

void foo() { cout << "foo" << endl; }

class MenuItem {
  std::function<void()> handler;
public:
  MenuItem() : handler(nullptr) {}

  void setHandler(std::function<void()> h) {
    handler = h;
  }

  virtual void command() {
    handler();
  }
};

int main() {
  Dialog dlg;
  MenuItem m1, m2;

  m1.setHandler(&foo);  // foo();
  m2.setHandler(bind(&Dialog::open, &dlg));  // Dialog::close()

  m1.command();
  m2.command();
}




#if 0
int main() {
  function<void()> fp;

  fp = &foo;
  fp();

  Dialog dlg;
  fp = bind(&Dialog::open, &dlg);  /// Dialog.open(this = &dlg)
  fp();

}
#endif
