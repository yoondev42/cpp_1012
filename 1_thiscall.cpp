// Design Pattern
//  => 건축
//  => 에릭감마
//     : 잘만들어진 소프트웨어의 설계에 공통된 설계의 특징이 존재한다.
//  => 에릭감마 외 3명
//      1995년 23가지로 정리한 디자인 패턴

// C++ Idioms
//  => C++ 언어를 이용해서, 문제를 해결할 때 사용하던 관용 설계 방법


#include <iostream>
using namespace std;

class Point {
  int x;
  int y;
public:
  // thiscall: 멤버 함수의 함수 호출 규약(Calling convention)
  // void set(Point* const this, int a, int b) {
  //    this->x = a;
  //    this->y = b;
  // }

  void set(int a, int b) {
    x = a;
    y = b;
  }

  // 정적 멤버 함수 안에서는 멤버 변수에 대한 접근이 불가능하다.
  // static void foo() {}
  static void foo() {

  }
};

int main() {
  Point p1;
  Point p2;

  // 멤버 함수를 호출하면, 객체의 주소가 암묵적으로 전달된다.
  p1.set(10, 20);   // Point::set(&p1, 10, 20)
  p2.set(20, 30);   // Point::set(&p2, 20, 30)

  Point::foo();     // Point::foo()
}