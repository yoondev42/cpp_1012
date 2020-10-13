#include <iostream>
using namespace std;

// 이벤트 처리 설계 방법
//  : 매우 중요합니다.

class MenuItem {
public:
  MenuItem() {}

  virtual void command() {
    // 메뉴가 선택된 사실을 다시 외부로 알려야 한다.
    // "객체가 외부로 이벤트를 발생한다." 라고 표현합니다.
  }
};

int main() {
  MenuItem m;
  m.command();
}