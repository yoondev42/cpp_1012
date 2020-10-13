#include <iostream>
using namespace std;

// 1. 인터페이스 기반의 리스너 개념 => 전략 패턴
//    : Java, C++(Tizen)

// 메뉴 이벤트를 처리하고 싶은 모든 클래스는 아래 인터페이스를 구현해야 한다.
struct IMenuListener {
  virtual ~IMenuListener() {}

  virtual void onCommand(int id) = 0;
};

class MenuItem {
  int id;
  IMenuListener* listener;
public:
  MenuItem(int i) : id(i), listener(nullptr) {}

  void setListener(IMenuListener* p) { listener = p; }

  virtual void command() {
    if (listener) {
      listener->onCommand(id);
    }
  }
};

class Dialog : public IMenuListener {
  void open() {
    cout << "Dialog open" << endl;
  }

  void close() {
    cout << "Dialog close" << endl;
  }

  // 메뉴 이벤트가 발생하게 되면, 아래 함수가 호출될 것이고, 아래 함수에서 원하는 동작을 수행하면 됩니다.
  //  문제점: 어떤 메뉴 객체로부터 이벤트가 발생했는지 여부를 알 수 없다.
  //   => 인터페이스에 어떤 객체로부터 이벤트가 발생했는지 식별하는 정보가 추가되어야 한다!
  void onCommand(int id) override {
    switch (id) {
      case 100:
        open();
        break;
      case 200:
        close();
        break;
    }
    
  }
};

int main() {
  MenuItem m(100);
  MenuItem m2(200);

  Dialog dlg;

  m.setListener(&dlg);
  m2.setListener(&dlg);

  m.command();
  m2.command();
}