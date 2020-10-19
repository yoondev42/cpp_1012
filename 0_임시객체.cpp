#include <iostream>
using namespace std;

class Test {
public:
  Test(int n) {
    cout << "Test()" << endl;
  }

  ~Test() {
    cout << "~Test()" << endl;
  }

  Test(const Test& t) {
    cout << "Test(const Test&)" << endl;
  }
};

// void foo(Test t) {

// }

// 반환용 '임시객체'에 복사해서, 반환한다.
Test foo() {
  Test t(32);
  return t;
  // return Test();
}

void goo(const Test& t) {

}

// 임시 객체를 직접 생성하는 문법
//  TYPE()
int main() {

  goo(Test(42));

  // foo();
  // int n = int();
  // Test t = Test(10);

  // 임시 객체를 Test&을 통해서 참조가 불가능하다.
  // Test& t = Test(10);

  // 임시 객체를 const Test&를 통해서 참조가 가능하다.
  const Test& t = Test(10);

  // 임시 객체를 T&&를 통해서 참조가 가능하다.
  Test&& t2 = Test(10);
}

