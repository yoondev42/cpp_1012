// 3_가상함수의원리.cpp
// 1) 함수 바인딩
//    p->Cry()를 어떤 함수와 연결할 것인가?
//  1. static binding
//      : 컴파일 시간에 컴파일러가 결정한다.
//        p의 포인터 타입을 통해 결정한다.

//  2. dynamic binding
//      : 컴파일 시간에 p의 메모리를 조사하는 기계어 코드 생성한다.
//        실행시간에 메모리 조사 후 호출
//        p포인터가 참조하는 객체의 타입을 실행시간에 조사해서 호출한다.
//      => 가상 함수 테이블
//          1) 모든 객체 크기가 8 byte 증가(가상 함수 테이블을 가르키는 포인터 크기)
//          2) 가상 함수의 개수 * 클래스의 개수 = 가상 함수 테이블

#include <iostream>
using namespace std;

class Animal {
public:
  virtual void Cry() { cout << "Animal Cry" << endl; }
};

class Dog : public Animal {
public:
  void Cry() { cout << "Dog Cry" << endl; }
};


int main() {
  Animal a; Dog d;
  Animal* p = &d;
  p->Cry(); 

  // (*(p->vfptr))[0]();

  // Animal a;
  // a.Cry();
  // Dog d;
  // d.Cry();
}