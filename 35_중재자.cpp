// 중재자 패턴
#include <vector>
#include <iostream>
using namespace std;



class CheckGroup;
class CheckBox {
  bool state;
  CheckGroup* group;
public:
  CheckBox() : state(false) {}

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
  printf("%p 객체 - 상태 변경: %d\n", b);
}


// 설문 조사
// 1. 오직 한개만의 객체를 생성하고 언제 어디서든 접근할 수 있는 디자인 패턴?
//  [ ] 팩토리 메소드 
//  [ ] 추상 팩토리
//  [x] 싱글톤
//  [ ] 빌더

int main() {
  CheckBox c1;
  CheckBox c2;
  CheckBox c3;
  CheckBox c4;

  CheckGroup group;
  c1.SetGroup(&group);
  c2.SetGroup(&group);
  c3.SetGroup(&group);
  c4.SetGroup(&group);

  c1.SetChecked(true);

}