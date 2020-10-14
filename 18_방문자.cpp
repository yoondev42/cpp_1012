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

int main() {
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  // s 안의 모든 값을 2배 증가하고 싶다.
  //  문제점: 특정 작업을 수행하는 멤버 함수가 제공되지 않는다.
  //        라이브러리의 사용자는 라이브러리의 기능을 추가하거나 변경하는 것이 불가능하다.
  //  만약 컨테이너가 '방문자 패턴'으로 구현되어 있다면, 사용자는 쉽게 기능을 확장할 수 있다.



}