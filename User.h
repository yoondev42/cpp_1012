// User.h
#include <string>

class UserImpl;
class User {
public:
  User(const std::string& n, int a);
  void Go();

private:
  UserImpl* pImpl;
};


// 아래 처럼 코드를 수정한 경우,
// User.h를 포함하는 모든 소스 파일은 다시 컴파일 되어야 한다.
#if 0
#include <string>
class User {
public:
  User(const std::string& n, int a);

  void Go();

private:
  std::string name;
  int age;
};
#endif


