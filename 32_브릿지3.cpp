

// 헤더에 있는 구현을 감추고 싶을 때
//  => pImpl Idiom(Bridge Pattern)


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
