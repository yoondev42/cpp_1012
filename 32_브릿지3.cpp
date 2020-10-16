

// 
//  => pImpl Idiom(Bridge Pattern)
//   1) 헤더에 있는 구현을 감추고 싶을 때
//   2) C/C++ 문제점
//     => 헤더 파일로 인한 의존성으로 인해 컴파일이 오래 걸린다.
//     => 컴파일러 방화벽

//   Exceptional C++ Series
//      1. Exceptional C++
//      2. More Exceptional C++
//      3. Exceptional C++ Style
//      "pImpl"


#include "User.h"

int main() {
  User user("Tom", 42);
  user.Go();
}


#if 0
// $g++ 32_브릿지3.cpp User.cpp
#include "User.h"

// User class를 다른 사람에게 전달해서 사용하게 만들고 싶다면,
//  cpp파일을 컴파일한 .o 파일과 헤더를 제공해야 합니다.

int main() {
  User user("Tom", 42);
  user.Go();
}
#endif


#if 0
// User.h
#include <string>
class User {
public:
  void Go();

private:
  std::string name;
  int age;
};

// User.cpp
#include "User.h"

#include <iostream>
using namespace std;

void User::Go() {
  cout << "User - Go" << name << ", " << age << endl;
}
#endif
