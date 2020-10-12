
#include <iostream>
#include <algorithm>  // sort

inline bool cmp1(int a, int b) { return a > b; }
inline bool cmp2(int a, int b) { return a < b; }

#include <functional>  // less<>, greater<> 함수 객체가 이미 제공됩니다.
using namespace std;

// 함수 객체
//   => 익명의 함수 객체
//      람다(Lambda)
int main() {
  int x[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

  sort(x, x + 10, [](int a, int b) {
    return a < b;
  });

  for_each(x, x + 10, [](int n) {
    cout << n << endl;
  });

  // for (int e : x) {
  //   cout << e << endl;
  // }
}

#if 0
int main() {
  int x[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

  // 정책을 함수 객체를 사용할 때
  // 장점: 정책이 인라인 치환이 가능하다. 빠르다!
  // 단점: 정책을 교체한 횟수 만큼의 sort() 기계어 코드 생성
  std::less<int> f1;
  std::sort(x, x + 10, f1);
  std::greater<int> f2;
  std::sort(x, x + 10, f2);

  for (int e : x) {
    cout << e << endl;
  }

  // [x, x+10)
  // 정책을 일반함수로 사용할 때
  // 장점: 정책을 여러번 교체해도, sort() 기계어는 하나이다.
  // 단점: 정책이 인라인 치환되지 않으므로 성능 저하가 있다.
  std::sort(x, x + 10, cmp1);
  std::sort(x, x + 10, cmp2);
}
#endif


// 공통성과 가변성의 분리
// 1. 일반 함수 변해야 하는 정책
//     => 변하는 것을 함수 인자화 한다.
//     => 함수 인자화
//        함수 포인터 기반      - 코드 메모리 사용량은 적지만, 인라인화가 불가능하다.
//        함수 객체(템플릿 기반) - 코드 메모리 사용량은 증가하지만, 인라인화로 빠르다.

// 2. 멤버 함수 변해야 하는 정책
//    A. 변하는 것을 가상 함수로 => Template Method Pattern
//             : 정책의 재사용성이 좋지 않다.
//    B. 변하는 것을 인터페이스 기반 다른 클래스로 => Strategy Pattern
//             : 정책의 재사용성이 좋다.
//               실행시간에 정책을 교체하는 것이 가능하다.

// 3. 실행 시간에 정책을 변경할 필요가 없다면
//     => 변하는 것을 템플릿 인자로 분리한다.(단위 전략)
//     => 인라인화 가능한 코드를 생성할 수 있기 때문에 빠르다.
//        실행시간에 정책을 교체하는 것이 불가능하다.