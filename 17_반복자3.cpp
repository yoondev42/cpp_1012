
#include <iostream>
using namespace std;

template <typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 c) {
  while (first != last && *first != c) 
    ++first;

  return first; // == last ? 0 : first;
}

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

#include <algorithm>

int main() {
  slist<int> s;
  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  slist<int>::iterator p = find(s.begin(), s.end(), 20);
  if (p != s.end()) {
     cout << *p << endl;
  }
}

// Iterator Pattern
//  의도: 컨테이너(컬렉션)의 내부 구조에 상관없이 요소를 열거한다.

// C++ 반복자 종류
// : 컬렉션의 구현 방식에 따라 지원할 수 있는 연산의 종류가 다르다.
// 1. 입력 반복자: =*p, ++
// 2. 출력 반복자: *p=, ++
// 3. 전진 반복자: 입출력 반복자, ++ 
// 4. 양방향 반복자: 입출력, ++, --
// 5. 임의접근 반복자: 입출력, ++, --, +, -, []    => 연속된 메모리