
// 일반적 프로그래밍(일반화 프로그래밍)
// = Generic Programming
#include <iostream>
using namespace std;

// C++ 라이브러리를 이해하기 위해서는 반드시 일반화를 이해해야 합니다.
// C++ = 객체 지향 + 일반화(Generic)

// C의 문자열 검색 함수
// 1. 검색 구간의 일반화: 부분 문자열 검색이 가능해야 한다.

// first
// |
// abcdefg
//         |
//        last
// [first, last): 반개구간

// 2. 검색 대상 타입의 일반화: template
// template <typename T>
// T* xstrchr(T* first, T* last, T c)
// 1. 위처럼 만들면, 구간의 타입과 찾는 요소의 타입이 연관되어 있다.
//    double 배열에서 int 타입을 찾는 행위를 할 수 없다.
// 2. T* 라고 하면 진짜 포인터만 사용할 수 있다. 스마트 포인터를 사용하는 것이 불가능하다.


template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 c) {
  while (first != last && *first != c) 
    ++first;

  return first; // == last ? 0 : first;
}

int main() {
  int x[] = { 1, 2, 3, 4, 5 };
  int *p2 = xfind(x, x + 5, 3);
  if (p2 != x + 5) {
    cout << *p2 << endl;
  }

  double a[] = { 1, 2, 3, 4, 5};
  double* p = xfind(a, a + 5, 3);
  if (p != a + 5) {
    cout << *p << endl;
  }
}

#if 0
int main() {
  char s[] = "abcdefg";

  char* p = xstrchr(s + 1, s + 4, 'd');
  if (p != s + 4) {
    cout << *p << endl;
  }
}
#endif


#if 0
char* xstrchr(char* s, int c) {
  while (*s != '\0' && *s != c)
    ++s;
  return *s == c ? s : (char*)0;
}


int main() {
  char s[] = "abcdefg";

  char* p = xstrchr(s, 'c');
  if (p != 0) {
    cout << *p << endl;
  }
}
#endif