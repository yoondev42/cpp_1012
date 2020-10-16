// State Pattern
#include <iostream>
using namespace std;

// 방법 2. 변하는 것을 가상함수로 - item에 따라 동작은 변한다.

class Hero {
public:
  int gold;
  int itemState;
public:
  virtual void Run()    { cout << "Hero Run" << endl;   }
  virtual void Attack() { cout << "Hero Attack" << endl;}
};

// 아이템의 획득에 따라 동작을 변경하기 위해
// 상속을 이용해보자.
class FastHero : public Hero {
public: 
  virtual void Run() {
    cout << "Hero Fast Run" << endl;
  }
};

class SlowHero : public Hero {
public:
  virtual void Run() {
    cout << "Hero Slow Run" << endl;
  }
};

class SuperFastHero : public Hero {
public:
  virtual void Run() {
    cout << "Hero Super Fast Run" << endl;
  }
};

// Hero의 상태에 따른 동작이 변경이 되는 것이 아니라,
// Hero가 변경된 것이다.

int main() {
  Hero h;
  h.gold = 100;

  FastHero fh;
  SlowHero sh;
  SuperFastHero sfh;

  // 객체가 변경되기 때문에 동작이 변경되는 것이다.
  // 다른 객체 상태가 공유되지 않는다.
  Hero* p = &h;
  p->Run();

  p = &fh;
  p->Run();

  p = &sfh;
  p->Run();  
}