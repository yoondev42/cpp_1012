// 29_데코레이터.cpp
#include <iostream>
using namespace std;

class Ticket {
public:
  void print() {
    cout << "작은 음악회 - 2020.12.25" << endl;
  }
};

// 상속: 기존 클래스에 기능을 추가할 수 있는 방법
class Ad1 : public Ticket {
public:
  void print() {
    Ticket::print();                // 원래 기능을 사용한 후에
    cout << "자동차 광고" << endl;     // 새로운 기능 추가
  }
};

class Ad2 : public Ad1 {
public:
  void print() {
    cout << "TV 광고" << endl;
    Ad1::print();
  }
};

// 상속: 새로운 클래스를 만든다.
//      정적인 기능의 추가
// 포함: 새로운 클래스를 만드는 것이 아니라, 기존 클래스의 기능을 실행시간에 확장할 수 있다.

int main() {
  // Ticket t;
  Ad1 t;
  // Ad2 t;
  t.print();
}