// State Pattern
#include <iostream>
using namespace std;

// 방법 2. 변하는 것을 가상함수로 - item에 따라 동작은 변한다.

class Hero {
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

int main() {
  Hero h;
  FastHero fh;
  SlowHero sh;
  SuperFastHero sfh;

  Hero* p = &h;
  p->Run();

  p = &fh;
  p->Run();

  p = &sfh;
  p->Run();  
}