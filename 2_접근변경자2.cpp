
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
// 2. 

template <typename T>
class stack : public list<T> {
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

int main() {
  stack<int> s;
  s.push(10);
  s.push(20);
  s.push(30);

  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
}