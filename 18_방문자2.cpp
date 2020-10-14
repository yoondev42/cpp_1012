#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 방문자 패턴은 복합 객체(Composite Pattern)와 연동되어 사용하기 좋습니다.
// 9_Menu.cpp

// 메뉴 시스템에 적용되는 방문자의 인터페이스
class PopupMenu;
class MenuItem;
struct IMenuVisitor {
  virtual ~IMenuVisitor() {}

  virtual void visit(PopupMenu* p) = 0;
  virtual void visit(MenuItem* p) = 0;
};

struct IMenuAcceptor {
  virtual ~IMenuAcceptor() {}

  virtual void accept(IMenuVisitor* visitor) = 0;
};


class BaseMenu : public IMenuAcceptor {
  std::string title;
public:
  BaseMenu(const std::string& s) : title(s) {}
  virtual ~BaseMenu() {}

  std::string getTitle() const { return title; }
  void setTitle(const std::string& s) { title = s; } // !!!!!

  virtual void command() = 0;
};

class MenuItem : public BaseMenu {
public:
  MenuItem(const std::string& s) : BaseMenu(s) {}

  void command() override {
    cout << getTitle() << "이 선택됨" << endl;
    getchar();
    getchar();
  }

  void accept(IMenuVisitor* p) override {
    p->visit(this);
  }
};

class PopupMenu : public BaseMenu {
  std::vector<BaseMenu*> v;          // 재귀적 포함
public:
  PopupMenu(const std::string& s) : BaseMenu(s) {}

  void accept(IMenuVisitor* p) override {
    p->visit(this);

    // 복합객체가 포함하고 있는 모든 메뉴들에 대해 방문자를 전달해야 한다.
    for (BaseMenu* e : v) {
      e->accept(p);
    }
  }

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

//--------------------------------
// 이제 메뉴 시스템에 다양한 기능을 추가하는 방문자들을 제공하면 됩니다.
// 메뉴 관련 클래스에 새로운 멤버 함수를 추가하지 않아도 기능을 확장할 수 있는 효과를 누립니다.
class TitleDecorationVisitor : public IMenuVisitor {
public:
  void visit(PopupMenu* p) override {
    string s = p->getTitle();
    string s2 = string("[") + s + string("]");

    // 캡슐화 위배
    //  : 방문자 패턴으로 인해서 읽기 전용으로 설계했던 멤버 데이터에 대한 수정이 가능하도록 변경해야 한다.
    p->setTitle(s2);
  }

  void visit(MenuItem* p) override {

  }
};

int main() {
  PopupMenu* menubar = new PopupMenu("MENUBAR");
  PopupMenu* p1 = new PopupMenu("화면 설정");
  PopupMenu* p2 = new PopupMenu("소리 설정");

  menubar->addMenu(p1);
  menubar->addMenu(p2);

  p1->addMenu(new MenuItem("해상도 설정"));
  p1->addMenu(new MenuItem("색상 설정"));
  p1->addMenu(new MenuItem("기타 설정"));

  p2->addMenu(new MenuItem("볼륨 설정"));
  p2->addMenu(new MenuItem("음향 설정"));

  //-----
  TitleDecorationVisitor v;
  menubar->accept(&v);
  //-----

  menubar->command();
  



}