#include <iostream>
using namespace std;
// 방문자(visitor) 패턴

// Itearator: 컨테이너(복합객체)의 내부 구조에 상관없이 요소를 '열거'한다.
// Visitor: 컨테이너(복합객체)의 내부 구조에 상관없이 요소에 '연산'을 수행한다.

template <typename T>
struct node {
  T data;
  node* next;

  node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
struct IVisitor {
  virtual ~IVisitor() {}

  virtual void visit(T& n) = 0;
};

// 모든 방문의 대상(컨테이너, 복합객체)은 아래의 인터페이스를 구현해야 합니다.
template <typename T>
struct IAcceptor {
  virtual ~IAcceptor() {}

  virtual void accept(IVisitor<T>* visitor) = 0;
};

template <typename T>
class slist : public IAcceptor<T> {
  node<T>* head;
public:
  //-------------
  // 방문자 패턴은 아래 함수를 정확히 이해하면 됩니다.
  void accept(IVisitor<T>* visitor) override {
    node<T>* current = head;

    while (current) {
      visitor->visit(current->data);
      current = current->next;
    }
  } 

  //-------------
  slist() : head(nullptr) {}

  void push_front(const T& a) {
    head = new node<T>(a, head);
  }

  const T& front() { return head->data; }
};
//------------------------
// 사용자는 IVisitor의 인터페이스의 구현을 통해, slist에 새로운 기능을 확장할 수 있다.
template <typename T>
class TwiceVisitor : public IVisitor<T> {
public:
  void visit(T& n) override {
    n *= 2; 
  }
};

template <typename T>
class PrintVisitor : public IVisitor<T> {
public:
  void visit(T& n) override {
    cout << n << endl;
  }
};

// C++의 컨테이너는 방문자 패턴을 지원하지 않습니다.
// 이유: 반복자를 통해서 해당 방문자의 동작을 동일하게 하는 것이 가능합니다.

#include <list>
#include <algorithm>  // for_each

void twice(int& n) {
  n *= 2;
}

void print(int n) {
  cout << n << endl;
}

struct Twice {
  void operator()(int& n) const {
    n *= 2;
  }
};

struct Print {
  void operator()(int n) const {
    cout << n << endl;
  }
};


int main() {
  list<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  for_each(s.begin(), s.end(), Twice());
  for_each(s.begin(), s.end(), Print());

  // for_each(s.begin(), s.end(), twice);
  // for_each(s.begin(), s.end(), print);
}



#if 0
int main() {
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  TwiceVisitor<int> v;
  s.accept(&v);

  PrintVisitor<int> v2;
  s.accept(&v2);

  // cout << s.front() << endl;


  // s 안의 모든 값을 2배 증가하고 싶다.
  //  문제점: 특정 작업을 수행하는 멤버 함수가 제공되지 않는다.
  //        라이브러리의 사용자는 라이브러리의 기능을 추가하거나 변경하는 것이 불가능하다.
  //  만약 컨테이너가 '방문자 패턴'으로 구현되어 있다면, 사용자는 쉽게 기능을 확장할 수 있다.



}
#endif

#if 0
class Animal {
public:
  virtual ~Animal() { cout << "Animal" << endl; }
};

class Dog : public Animal {
public:
  ~Dog() { cout << "Dog" << endl; }
};

int main() {
  // Dog d;
  Animal* p = new Dog;
  delete p;
}
#endif