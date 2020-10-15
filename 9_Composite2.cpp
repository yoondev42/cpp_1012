
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Composite 패턴
//  1. 단일 객체와 복합 객체가 공통의 부모를 가지고, 복합 객체는 부모를 포함하는 형태의 설계
//  2. 단일 객체와 복합 객체를 사용하는 방법을 동일하게 한다 - 다형성

// MenuItem
// PopupMenu

class BaseMenu {
  string title;
public:
  BaseMenu(const string& s) : title(s) {}

  string getTitle() const { return title; }

  // 단일 객체와 복합 객체를 사용하는 방법이 동일해야 한다.
  // => 단일 객체와 복합 객체는 동일시 된다.
  virtual void command() = 0;
};

class MenuItem : public BaseMenu {
public:
  MenuItem(const string& s) : BaseMenu(s) {}

  void command() override {
    cout << getTitle() << " 메뉴가 선택됨" << endl;
    getchar();
    getchar();
  }
};

// PopupMenu는 MenuItem도 포함해야 하지만, 자기 자신도 포함해야 한다.
// => MenuItem과 PopupMenu는 '공통의 부모'를 가져야 한다.
//   아래처럼 부모를 포함할 수 있는 형태의 설계 - 재귀적 합성 => 복합 객체

class PopupMenu : public BaseMenu {
  string title;
  vector<BaseMenu*> v;
public:
  PopupMenu(const string& s) : BaseMenu(s) {}

  void addMenu(BaseMenu* p) { v.push_back(p); }

  void command() override {
    while (1) {
      system("clear");
      int len = v.size();
      for (int i = 0 ; i < len; ++i) {
        cout << i + 1 << ". " << v[i]->getTitle() << endl;
      }
      cout << len + 1<< ". 상위 메뉴로" << endl;

      int cmd;
      cin >> cmd;
      if (cmd == len + 1)
        break;

      v[cmd - 1]->command();     
    }
  }
};

int main() {
  PopupMenu* root = new PopupMenu("ROOT");
  PopupMenu* p1 = new PopupMenu("화면");
  PopupMenu* p2 = new PopupMenu("소리");

  root->addMenu(p1);
  root->addMenu(p2);

  p1->addMenu(new MenuItem("화면 조정"));
  p1->addMenu(new MenuItem("색감 조정"));

  p2->addMenu(new MenuItem("소리 조정"));
  p2->addMenu(new MenuItem("볼륨 조정"));

  root->command(); 
}