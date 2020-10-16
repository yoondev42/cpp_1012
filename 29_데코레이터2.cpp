#include <iostream>
using namespace std;


// 재귀적 합성을 사용하는 디자인 패턴
// 1. Composite Pattern - 복합 객체의 구성
// 2. Decorator Pattern - 런타임에 객체의 기능을 추가하는 방법

struct Item {
  virtual ~Item() {}
  virtual void print() = 0;
};

class Ticket : public Item {
public:
  void print() override {
    cout << "작은 음악회 - 2020.12.25" << endl;
  }
};


// 모든 포장지(광고)의 공통의 특징을 부모로 제공하자.
class Decorator : public Item {
  Item& ticket;
public:
  Decorator(Item& t) : ticket(t) {}
  void print() { 
    ticket.print();
  }
};

class Ad1 : public Decorator {
public:
  Ad1(Item& t) : Decorator(t) {}

  void print() {
    Decorator::print();
    cout << "자동차 광고" << endl;
  }
};

class Ad2 : public Decorator {
public:
  Ad2(Item& t) : Decorator(t) {}

  void print() {
    cout << "TV 광고" << endl;
    Decorator::print();
  }
};

// Decorator Pattern
//  1. 포함을 통해 실행시간에 기능을 추가한다.
//  2. 포장지는 객체를 포장하지만, 포장된 객체를 다시 포장할 수 있어야 한다.!!!!!
//     => 포장지와 객체는 동일 부모를 가져야 한다.

int main() {
  Ticket ticket;
  Ad1 ad1(ticket);

  // ad1.print();
  Ad2 ad2(ad1);
  ad2.print();

  // Ad1 ad1(ticket);
  // ad1.print();

  // Ad2 ad2(ticket);
  // ad2.print();
}