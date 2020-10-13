#include <iostream>
using namespace std;

// 객체의 생성을 N개로 제한하는 방법
//  1. 객체의 개수를 카운트하기 위해선 정적 멤버 변수를 이용해야 한다.
//  2. 객체 생성을 실패하기 위해서는 생성자에서 '예외'를 던져야 한다.

// 객체 생성 개수를 제한하는 로직을 부모 클래스를 통해 제공한다.

// 아래 코드의 문제점
//  - 부모의 타입이 동일하기 때문에, 정적 데이터를 공유하게 된다.
//    각 타입에 따라 분리해야 한다.
//    => CRTP


template <typename T, int N>
class LimitMaxObject {
  static int count;
public:
  LimitMaxObject() {
    if (++count > N) 
      throw 1;
  }

  ~LimitMaxObject() {
    --count;
  }
};


// 정적 데이터를 분리하는 기술입니다.
template <typename T, int N>
int LimitMaxObject<T, N>::count = 0;


class Mouse : public LimitMaxObject<Mouse, 5> {  
};

class Image : public LimitMaxObject<Image, 5> {
};

int main() {
  Mouse m[3];
  Image i[3];
}


#if 0
template <int N>
class LimitMaxObject {
  static int count;
public:
  LimitMaxObject() {
    if (++count > N) 
      throw 1;
  }

  ~LimitMaxObject() {
    --count;
  }
};

template <int N>
int LimitMaxObject<N>::count = 0;

class Mouse : public LimitMaxObject<5> {  
};

class Image : public LimitMaxObject<5> {
};

int main() {
  Mouse m[3];
  Image i[3];
}
#endif