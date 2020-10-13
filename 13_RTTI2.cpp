
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

class Animal {
public:
  static CRuntimeClass classAnimal;

  virtual CRuntimeClass* GetRuntimeClass() {
    return &classAnimal;
  }
};

CRuntimeClass Animal::classAnimal = { "Animal" };

class Dog : public Animal {
public:
  static CRuntimeClass classDog;

  virtual CRuntimeClass* GetRuntimeClass() {
    return &classDog;
  }
};

CRuntimeClass Dog::classDog = { "Dog" };

void foo(Animal* p) {
  // p가 Dog인지 조사하는 방법 -> RTTI
  // if (typeid(*p) == typeid(Dog)) {
  //      
  // }

  if (p->GetRuntimeClass() == &Dog::classDog) {
    cout << "Dog" << endl;
  }

  cout << p->GetRuntimeClass()->name << endl;
}

int main() {
  Animal d;
  foo(&d);
}







