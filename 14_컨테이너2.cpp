// 컨테이너 설계의 기술

#include <iostream>
using namespace std;

// 1. object* 기반 컨테이너
//    부모의 포인터 타입은 자식 객체를 참조할 수 있다.(Upcasting)

// 약속: 프로그램 내의 모든 클래스는 object 기반의 클래스이다.
//    ex) Java, C#에서 클래스는 모두 Object의 자식입니다.
//       Java, C#에서는 Object 기반의 컨테이너를 사용하고 있습니다.

class object {
public:
  virtual ~object() {}
};

class Dialog : public object {};
class Point : public object {};
class Rect : public object {};

//------------

struct node {
  object* data;
  node* next;

  node(object* a, node* n) : data(a), next(n) {}
};

class slist {
  node* head;
public:
  slist() : head(nullptr) {}

  void push_front(object* a) {
    head = new node(a, head);
  }

  object* front() { return head->data; }
};

// slist는 object 기반의 모든 클래스 타입의 객체를 저장하는 것이 가능하다.

// 문제점
//  1. s.front()를 통해 얻은 객체를 사용하기 위해서는 다운 캐스팅이 필요하다.
//  2. built-in 타입을 저장하는 것이 불가능하다.
//     int, char, double, float ...
//     => 표준 타입에 대한 래퍼 클래스가 필요하다.
//  3. 타입 안정성이 떨어진다.
//     컨테이너에 여러 개의 타입을 저장하는 경우보다, 하나의 타입을 저장하는 경우가 많다.
//     실수로 다른 타입을 넣어도 컴파일 시간에 오류가 발생하지 않는다.
//   Java/C# - 컴파일러가 위의 해당하는 코드를 자동으로 지원하는 기술

// 장점
//  템플릿은 코드를 생성하는 기술이기 때문에, 코드 메모리 사용량이 증가한다.
//  object* 기반의 컨테이너는 템플릿을 이용하지 않기 때문에 코드 메모리 사용량은 증가하지 않는다.


class Integer : public object {
  int n;
public:
  Integer(int a) : n(a) {}
  int getValue() const { return n; }
};

int main() {
  slist s;
  s.push_front(new Point);
  s.push_front(new Dialog);
  s.push_front(new Rect);
  
  Rect* r = dynamic_cast<Rect*>(s.front());
  if (r) {
    // Rect의 기능을 이용한다.
  }

  s.push_front(new Integer(10));  // s.push_front(10); -> s.push_front(new Integer(10)); - Auto Boxing
  s.push_front(new Integer(20));

  int n = dynamic_cast<Integer*>(s.front())->getValue();  // Auto Unboxing


  // cout << s.front() << endl;
}