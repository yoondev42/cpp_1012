
// stack을 만들어봅시다.
//  LIFO: Last in first out

// list가 이미 있습니다.
#include <list>
#include <iostream>
using namespace std;

// Client가 stack을 요구합니다.
// 1. stack을 처음부터 만든다.
// 2. list를 한쪽으로 사용하면 stack이다. list를 재사용하자.
//  "바퀴를 재발명하지 말자."

// Adpater Pattern: 기존 클래스의 인터페이스(함수 이름)을 변경해서,
//                  사용자가 요구하는 새로운 클래스처럼 보이게하는 패턴

// OOP에서 기존 클래스를 재사용하는 방법
// 1. 상속


// 라이브러리 설계 원칙
// => 쉽게 사용할 수 있도록 만드는 것도 중요하지만,
//    잘못 사용하기 어렵게 만들어야 한다.

// private 상속: 부모로부터 구현은 물려받지만(자식이 내부적으로 사용하지만)
//              인터페이스는 물려 받지 않겠다.(부모 함수를 외부로 노출하지 않겠다.)
// => 접근 변경자를 통한 문법은 OOP언어가 범용적으로 제공하는 기능이 아닙니다.
#if 0
template <typename T>
class stack : private list<T> {
public:
  void push(const T& a) { 
    list<T>::push_back(a);
  }

  void pop() {
    list<T>::pop_back();
  }

  T& top() {
    return list<T>::back();
  }
};
#endif

#include <vector>
#include <deque>
#include <stack>
//      => list와 vector의 절충형태(연속된 메모리로 구현된 리스트)

// S/W의 재사용은 상속과 포함이 있습니다. => 포함이 좋을때가 많다.
// 2. 포함
//   => 공개하고자 하는 기능을 명시적으로 제공해야 한다.
//   => C++ STL의 stack은 list가 아닌 다른 컨테이너를 이용할 수 있는 설계도 적용되어 있습니다.

template <typename T, typename C = deque<T>>
class Stack {
  C st;
public:
  void push(const T& a) { 
    st.push_back(a);
  }

  void pop() {
    st.pop_back();
  }

  T& top() {
    return st.back();
  }
};

int main() {
  stack<int, list<int>> s;
  stack<int, vector<int>> s2;
  
  // s.pop_back();      // list의 기능을 이용한다!
  // s.push_front(20);


  s.push(10);
  s.push(20);
  s.push(30);

  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
}