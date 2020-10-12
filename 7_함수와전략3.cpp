// 1. 함수는 자신만의 타입이 존재하지 않는다.
//    시그니처(인자 정보, 반환 타입)이 동일한 모든 함수는 같은 타입이다.

// 2. 함수 객체
//    클래스/구조체를 통해서 정의하기 때문에, 모든 함수객체는 다른 타입이다.

#include <iostream>
using namespace std;

struct Plus {
  int operator()(int a, int b) const {
    return a + b;
  }
};

int main() {
  Plus p;

  cout << p(10, 20) << endl;
}