// 3_가상함수의원리2.cpp

#include <iostream>
using namespace std;


class A {
  int a;
public:
  void foo() { cout << "A foo" << endl; }
};

class B {
  int b;
public:
  virtual void goo() { cout << "B goo" << endl; }
};

int main() {
  A aaa;
  B* p = reinterpret_cast<B*>(&aaa);

  p->goo();   // 정적 바인딩: B::goo();
}             // 동적 바인딩: (*p)[0](); -> A::foo();