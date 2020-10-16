// User.cpp
#include "User.h"

#include <iostream>
using namespace std;

class UserImpl {
public:
  UserImpl(const std::string& n, int a);

  void Go();
private:
  std::string name;
  int age;
};

UserImpl::UserImpl(const std::string& n, int a) : name(n), age(a) {

}

void UserImpl::Go() {
  cout << "User - Go:" << name << ", " << age << endl;
}

User::User(const std::string& n, int a) {
  pImpl = new UserImpl(n, a);
}

void User::Go() {
  pImpl->Go();
}







#if 0
#include "User.h"

#include <iostream>
using namespace std;

User::User(const std::string& n, int a) : name(n), age(a) {

}

void User::Go() {
  cout << "User - Go:" << name << ", " << age << endl;
}
#endif