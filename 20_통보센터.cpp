#include <iostream>
using namespace std;
// Notification Center(통보센터) - iOS
//  프로그램 내에 발생하는 이벤트를 총괄 관리하는 객체

// C++에서 이벤트 '콜백'을 등록하는 2가지 형태
// 1. 함수(핸들러) 기반
// 2. 인터페이스 기반

#include <functional>
#include <map>
#include <vector>

// 이벤트 종류: string
// 이벤트 관찰자: vector<HANDLER>

// 프로그램 내에 관찰자 패턴이 엄청나게 많이 필요한 경우
// 모든 관찰자에 대한 부분을 종합적으로 관리할 수 있도록 해준다.
class NotificationCenter {
  using HANDLER = function<void()>;

  map<string, vector<HANDLER>> notifiMap;
public:
  void addObserver(string event, HANDLER handler) {
    notifiMap[event].push_back(handler);
  }

  void postNotificationWithName(string event) {
    vector<HANDLER>& v = notifiMap[event];
    for (HANDLER h : v) {
      h();
    }
  }
};

void foo() { cout << "foo" << endl; }
class Dialog {
public:
  void close() { cout << "Dialog close" << endl; }
};

int main() {
  NotificationCenter nc;

  Dialog dlg;

  nc.addObserver("LOWBATTERY", &foo);
  nc.addObserver("LOWBATTERY", bind(&Dialog::close, &dlg));

  nc.addObserver("FOO", &foo);
  nc.addObserver("GOO", &foo);

  // 배터리는 체크하는 모듈에서
  nc.postNotificationWithName("LOWBATTERY");
}