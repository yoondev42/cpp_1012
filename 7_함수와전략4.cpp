// 7_함수와전략.cpp
#include <iostream>
using namespace std;

struct Less {
  inline bool operator()(int a, int b) const {
    return a < b;
  }
};

struct Greater {
  inline bool operator()(int a, int b) const {
    return b > a;
  }
};

template <typename T>
void Sort(int* x, int n, T cmp) {
  for (int i = 0 ; i < n - 1; ++i) {
    for (int j = i + 1 ; j < n; j++) {
      if (cmp(x[i], x[j]))
        swap(x[i], x[j]);
    }
  }
}

inline bool cmp1(int a, int b) { return a > b; }
inline bool cmp2(int a, int b) { return a < b; }

// 핵심: 함수 객체를 정책으로 사용하기 위해서는
//      정책의 인자가 '템플릿'으로 제공되어야 합니다.
//      기존 함수도 정책으로 사용하는 것이 가능합니다.

//      장점: 인라인화가 가능하다.
//           정책에 대한 호출 오버헤드가 존재하지 않는다.
//      단점: 정책을 변경한 횟수만큼의 코드가 생성되어야 합니다.
//           코드 메모리 사용량 오버헤드가 존재한다.

int main() {
  Greater cmp;
  int x[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
  
  Sort(x, 10, cmp);
  // void Sort(int* x, int n, Greater cmp)

  Less l;
  Sort(x, 10, l);
  // void Sort(int* x, int n, Less cmp)

  // void Sort(int* x, int n, bool (*cmp)(int, int))
  Sort(x, 10, cmp1);

  // 위에서 생성된 함수 포인터 구현을 이용합니다.
  Sort(x, 10, cmp2);

  for (int e : x) {
    cout << e << endl;
  }
}