// State Pattern
#include <iostream>
using namespace std;

// 1. 아이템의 종류에 따른 조건 분기
// 문제점: 신규 아이템이 추가되면 조건 분기의 코드는 수정되어야 한다.
//       "OCP를 만족하지 않는다."
//        => 새로운 기능이 추가되어도 기존 코드는 수정되면 안된다.

enum Item {
  FAST_RUN_ITEM = 100,
  SLOW_RUN_ITEM,
  SUPERFAST_RUN_ITEM,
};

// 상태 패턴
class Hero {
  int gold;
  int itemState;
public:
  void SetItemState(int i) {
    itemState = i;
  }

  // Replace type code with Polymorphism
  void Run()    { 
    if (itemState == FAST_RUN_ITEM) {
      cout << "Hero Fast Run" << endl;
    } else if (itemState == SLOW_RUN_ITEM) {
      cout << "Hero Slow Run" << endl;
    } else {
      cout << "Hero Run" << endl;
    }
  }

  void Attack() { cout << "Hero Attack" << endl;}
};

int main() {
  Hero h;
  h.Run();

  h.SetItemState(SLOW_RUN_ITEM);
  h.Run();

  h.SetItemState(FAST_RUN_ITEM);
  h.Run();
}