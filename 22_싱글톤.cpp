// 22_싱글톤

#include <iostream>
using namespace std;

// Singleton Pattern
//  의도: 오직 한개의 객체만 만들 수 있고, 어디에서도 동일한 방법으로 객체를 얻을 수 있게 하는 패턴

class Cursor {
  // 규칙 1. private 생성자
private:
  Cursor() {}

  // 규칙 3. 복사와 대입을 금지 - delete function
  Cursor(const Cursor&) = delete;
  Cursor& operator=(const Cursor&) = delete;

public:
  // 규칙 2. 오직 한개만 만들어서 반환하는 정적 함수
  static Cursor& getInstance() {
    static Cursor instance;      // 내부 정적 변수
    return instance;
  }
};


// C++ 에서는 전역 객체를 사용하지 않는 것이 좋습니다.
//  => 생성자의 호출 시점과 소멸자의 호출 시점이 명확하게 정의되어 있지 않습니다.
//    문제점: 생성자가 호출되지 않은 객체에 접근하거나, 소멸자가 호출된 객체에 접근하는 문제가 발생할 수 있습니다.
// Cursor c;

int main() {
  Cursor& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  printf("%p %p\n", &c1, &c2);
}

