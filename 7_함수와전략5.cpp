
#include <iostream>
#include <algorithm>  // sort

inline bool cmp1(int a, int b) { return a > b; }
inline bool cmp2(int a, int b) { return a < b; }

#include <functional>  // less<>, greater<> 함수 객체가 이미 제공됩니다.
using namespace std;

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