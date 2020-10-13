// 13_RTTI.cpp
//  Runtime Type Information
//   : 실행 시간에 타입의 정보를 알아내는 기술

// 문제점
//  1. 가상 함수 테이블에 저장된 type_info 구조체 정보를 참고하고 있다.
//      해당 클래스가 가상 함수 테이블이 제공되지 않는다면, 제대로 타입에 대한 정보를 체크하는 것이 불가능하다.
//  2. 이름을 출력하였을 경우, 컴파일러마다 다른 구현을 사용하고 있다.

// => C++을 통해 구현된 많은 프레임워크들이 자체적으로 RTTI와 동일한 기능을 구현하고 있다.
//    Windows MFC / Android Framework C++

// RTTI 특성
//  => 클래스를 통해 꺼낼 수 있어야 한다.
//     객체를 통해 꺼낼 수 있어야 한다.


#include <iostream>
using namespace std;

class Animal {
public:
  virtual ~Animal() {}
};

class Dog : public Animal {
};


int main() {
  Dog d;
  Animal a;
  Animal* p = &d;

  const type_info& ti1 = typeid(a);
  cout << ti1.name() << endl;
  const type_info& ti2 = typeid(d);
  cout << ti2.name() << endl;


  // p가 Animal? Dog?
  if (typeid(*p) == typeid(Dog)) {
    cout << "Dog" << endl;
  } else if (typeid(*p) == typeid(Animal)) {
    cout << "Animal" << endl;
  }
}