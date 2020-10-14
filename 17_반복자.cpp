
// Iterator Pattern
//  의도: 컨테이너의 내부 구조에 상관없이 요소를 열거한다.
#include <iostream>
using namespace std;

template <typename T>
struct node {
  T data;
  node* next;

  node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
class slist_iterator {
  node<T>* current;
public:
  slist_iterator(node<T>* p = nullptr) : current(p) {}

  T& operator*() { return current->data; }
  slist_iterator& operator++() {
    current = current->next;
    return *this;
  }

  bool operator==(const slist_iterator& t) { return current == t.current; }
  bool operator!=(const slist_iterator& t) { return current != t.current; }
};

template <typename T>
class slist {
  node<T>* head;
public:
  using iterator = slist_iterator<T>;

  slist() : head(nullptr) {}

  void push_front(const T& a) {
    head = new node<T>(a, head);
  }

  const T& front() { return head->data; }

  slist_iterator<T> begin() { return slist_iterator<T>(head); }
  slist_iterator<T> end()   { return slist_iterator<T>(); }
};

// 1. 컨테이너의 설계자는 자신의 컨테이너를 열거할 수 있는 반복자를 제공해야 합니다.
// C++은 반복자의 동작을 연산자 재정의를 통해 제공하도록 약속하고 있습니다.
//  *     : 참조
//  ++    : 다음 위치로 이동
//  ==    : 동등성 비교
//  !=    : 동등성 비교
// 2. 모든 컨테이너는 자신의 처음과 끝을 가르키는 반복자를 꺼내는 방법을 제공해야 한다.
//    begin / end
// 3. 컨테이너의 설계자는 자신의 컨테이너의 반복자의 이름을 동일한 이름으로 약속해야 합니다.

#include <list>

int main() {
  list<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  // slist_iterator<int> iter = s.begin();
  list<int>::iterator iter = s.begin();

  while (iter != s.end()) {
    cout << *iter << endl;
    ++iter;
  }
}