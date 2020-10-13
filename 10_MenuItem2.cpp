#include <iostream>
using namespace std;

// 1. 인터페이스 기반의 리스너 개념
//    : Java, C++(Tizen)

// 메뉴 이벤트를 처리하고 싶은 모든 클래스는 아래 인터페이스를 구현해야 한다.
struct IMenuListener {
  virtual ~IMenuListener() {}

  virtual void onCommand() = 0;
};

class MenuItem {
  IMenuListener* listener;
public:
  MenuItem() : listener(nullptr) {}

  void setListener(IMenuListener* p) { listener = p; }

  virtual void command() {
    if (listener) {
      listener->onCommand();
    }
  }
};

class Dialog : public IMenuListener {
  void open() {
    cout << "Dialog open" << endl;
  }

  // 메뉴 이벤트가 발생하게 되면, 아래 함수가 호출될 것이고, 아래 함수에서 원하는 동작을 수행하면 됩니다.
  void onCommand() override {
    open();
  }
};

int main() {
  MenuItem m;
  Dialog dlg;

  m.setListener(&dlg);

  m.command();
}