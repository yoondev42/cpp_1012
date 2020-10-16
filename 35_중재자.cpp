// 중재자 패턴
#include <vector>
#include <string>
#include <iostream>
using namespace std;


class CheckGroup;
class CheckBox {
  bool state;
  string name;
  CheckGroup* group;
public:
  CheckBox(const std::string& s) : state(false), name(s), group(nullptr) {}

  void SetGroup(CheckGroup* p) {
    group = p;
  }

  void SetChecked(bool b);

  

  bool IsChecked() const { return state; }
};

class CheckGroup {
  vector<CheckBox*> checkboxes;
public:
  void AddCheckBox(CheckBox* p) {
    checkboxes.push_back(p);
    p->SetGroup(this);
  }

  void OnUpdate(CheckBox* p) {
    for (CheckBox* e : checkboxes) {
      if (p != e)
        e->SetChecked(false);
    }
  }
};

void CheckBox::SetChecked(bool b) {
  state = b;

  // 모든 체크박스는 자신의 상태가 체크 되었을 때, CheckGroup에게 알려준다.
  if (state) {
    group->OnUpdate(this);
  }

  printf("%s 객체 - 상태 변경: %d\n", name.c_str(), b);
}


// 설문 조사
// 1. 오직 한개만의 객체를 생성하고 언제 어디서든 접근할 수 있는 디자인 패턴?
//  [ ] 팩토리 메소드 
//  [ ] 추상 팩토리
//  [x] 싱글톤
//  [ ] 빌더

int main() {
  CheckBox c1("팩토리 메소드");
  CheckBox c2("추상 팩토리");
  CheckBox c3("싱글톤");
  CheckBox c4("빌더");
  CheckBox c5("템플릿 메소드");

  CheckGroup group;
  group.AddCheckBox(&c1);
  group.AddCheckBox(&c2);
  group.AddCheckBox(&c3);
  group.AddCheckBox(&c4);
  group.AddCheckBox(&c5);

  c1.SetChecked(true);
  cout << endl;
  c2.SetChecked(true);
  cout << endl;
  c3.SetChecked(true);
  cout << endl;
  c5.SetChecked(true);
  cout << endl;
}