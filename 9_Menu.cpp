// 9_Menu.cpp

// Menu를 객체 지향적으로 모델링 해보자.
// 1. PopupMenu
// 2. MenuItem

#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::cin;


// 핵심: PopupMenu
//   => MenuItem뿐 아니라 자기 자신과 동일한 타입도 포함할 수 있어야 한다.
//    : 단일객체(MenuItem)와 복합객체(PopupMenu)는 공통의 부모를 가져야 한다.
//      -> "재귀적 포함"을 구현한다.

// 클래스의 모든 필드는 private으로 만들어야 한다.
// 필드의 값을 읽거나 변경해야 하면, 반드시 메소드를 통해 구현되어야 한다.

class BaseMenu {
  std::string title;
public:
  BaseMenu(const std::string& s) : title(s) {}
  virtual ~BaseMenu() {}

  std::string getTitle() const { return title; }

  // 자식의 입장에서는 반드시 구현해야 하고, 부모는 구현을 제공할 필요가 없다면,
  // 순수 가상 함수로 만드는 것이 좋다.
  virtual void command() = 0;
};

class MenuItem : public BaseMenu {
public:
  MenuItem(const std::string& s) : BaseMenu(s) {}

  void command() override {
    cout << getTitle() << "이 선택됨" << endl;
  }
};

class PopupMenu : public BaseMenu {
  std::vector<BaseMenu*> v;          // 재귀적 포함
public:
  PopupMenu(const std::string& s) : BaseMenu(s) {}

  void addMenu(BaseMenu* p) { v.push_back(p); }

  void command() override {
    while (1) {
      system("clear");  // system("cls");
      int sz = v.size();
      for (int i = 0 ; i < sz; ++i) {
        cout << i+1 << ". " << v[i]->getTitle() << endl;
      }
      cout << sz+1 << ". 상위 메뉴로" << endl;

      cout << "메뉴를 선택하세요 >> ";
      int cmd;
      cin >> cmd;

      if (cmd == sz + 1)
        break;

      if (cmd < 1 || cmd > sz + 1) // 잘못된 입력
        continue;

      // 선택한 메뉴를 실행한다?
      // 어떻게 할까요?  
      v[cmd - 1]->command();   // 다형성
    }
  }
};

int main() {
  
}