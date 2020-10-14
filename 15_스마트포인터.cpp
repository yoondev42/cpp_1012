
// 스마트포인터
#include <iostream>
using namespace std;


// 포인터의 역활을 수행하는 클래스
//  개념: 임의의 객체가 다른 클래스의 포인터의 역활을 하는 것
//  원리: -> 연산자와 * 연산자를 재정의해서 포인터의 역활을 수행할 수 있도록 한다.


class Image {
public:
  Image() { cout << "Image 객체 생성" << endl; }
  ~Image() { cout << "~Image 객체 파괴" << endl; }

  void draw() { cout << "Image draw" << endl; }
};

// Proxy Pattern: 역활을 대신 하는 객체(클래스)
//     => 진짜 포인터가 아니라 객체이다.
//        생성/복사/대입/소멸의 모든 과정을 제어할 수 있다.
//       : Smart Proxy
template <typename T>
class Ptr {
  T* obj;
public:
  inline Ptr(T* p = 0) : obj(p) {}
  inline ~Ptr() { delete obj; }

  inline T* operator->() { return obj; }
  inline T& operator*() { return *obj; }
};

// C++ 의 이미 스마트포인터가 여러개 정의되어 있습니다.
//  => 소유권(ownership)
//   unique_ptr
//   shared_ptr / weak_ptr

int main() {
  Ptr<Image> p(new Image);

  p->draw();
  (*p).draw();

  // Image* p = new Image;
  // delete p;
}