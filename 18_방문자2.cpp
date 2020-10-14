#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 방문자 패턴은 복합 객체(Composite Pattern)와 연동되어 사용하기 좋습니다.
// 9_Menu.cpp


class BaseMenu {
  std::string title;
public:
  BaseMenu(const std::string& s) : title(s) {}
  virtual ~BaseMenu() {}

  std::string getTitle() const { return title; }
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

  menubar->command();
}