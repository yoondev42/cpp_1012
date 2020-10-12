#include <iostream>
using namespace std;

// 가상 함수: 실행 시간에 동작
// 디폴트 인자: 컴파일 시간에 결정된다.

// 가상함수에서는 되도록이면, 디폴트 인자를 사용하지 말자
// => 사용했다면, 재정의할 때 절대 변경하지 말자

class A {
public:
  virtual void foo(int a = 10) { cout << "A: " << a << endl; }
};

class B : public A {
public:
  void foo(int a = 20) override { cout << "B: " << a << endl; }
};

int main() {
  A* p = new B;
  p->foo();       // (*p)[0](p, 10) 라는 기계어 코드 생성!
}