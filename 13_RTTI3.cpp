
#include <iostream>
#include <string>
using namespace std;

// RTTI 핵심: type_info
//           정적 멤버 변수와 동일합니다.
struct CRuntimeClass {
  string name;
};

// 모든 클래스는 아래 규칙을 지켜야 합니다.
// 1. 모든 클래스에는 정적 멤버 변수인 CRuntimeClass가 있어야 한다.
// 2. 변수 이름도 동일 이름해야 합니다.
//     "class클래스이름"
//      ex) classAnimal / classDog
// 3. 정적 멤버 데이터를 반환하는 가상함수 GetRuntimeClass를 약속합니다.
// > 위의 규칙을 '매크로'를 통해 제공하면 편리합니다.

// ##: 토큰을 치환한 후 하나의 토큰으로 만들어준다.
//  #: 토큰을 치환한 후, 문자열로 만들어준다.

#define DECLARE_DYNAMIC(classname)            \
public:                                       \
static CRuntimeClass class##classname;        \
virtual CRuntimeClass* GetRuntimeClass();

#define IMPLEMENT_DYNAMIC(classname)                   \
CRuntimeClass* classname::GetRuntimeClass() {          \
  return &class##classname;                            \
}                                                      \
CRuntimeClass classname::class##classname = { #classname };

class Animal {
  DECLARE_DYNAMIC(Animal)
};

class Dog : public Animal {
  DECLARE_DYNAMIC(Dog)
};

IMPLEMENT_DYNAMIC(Animal)
IMPLEMENT_DYNAMIC(Dog)

#define RUNTIME_CLASS(classname)      &(classname::class##classname)


void foo(Animal* p) {
  // p가 Dog인지 조사하는 방법 -> RTTI
  // if (typeid(*p) == typeid(Dog)) {
  //      
  // }

  if (p->GetRuntimeClass() == &Dog::classDog) {
    cout << "Dog" << endl;
  }

  if (p->GetRuntimeClass() == RUNTIME_CLASS(Dog)) {
    cout << "Dog" << endl;
  }

  cout << p->GetRuntimeClass()->name << endl;
}

int main() {
  Dog d;
  foo(&d);
}







