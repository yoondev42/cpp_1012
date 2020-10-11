
// NULL 객체와 멤버 함수 호출
#include <iostream>
using namespace std;

// MFC, Android C++ 아래와 같은 코드를 발견할 수 있습니다.
class Sample {
  int data;
protected:
  int on_foo() {
    cout << "foo" << endl;
    return data;
  }
public:

  // Clang: 'this' pointer cannot be null in well-defined C++ code; pointer may be assumed to always convert to true
  // C++에서는 this가 nullptr일때, 멤버 함수 호출에 대한 부분은 undefined 입니다.
  //  => this가 nullptr인 것을 체크하는 코드는 안좋다.
  // int foo() {
  //   return this ? on_foo() : 0;
  // }

  static int foo(Sample* self) {
    return self ? self->on_foo() : 0;
  }

  // public:
  // int foo(Sample* const this)
  // int foo() {
  //   cout << "foo" << endl;
  //   return data;                // return this->data
  // }
};

int main() {
  Sample* p = new Sample;
  // p->foo();  // Sample::foo(p)
  Sample::foo(p);
}