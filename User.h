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
