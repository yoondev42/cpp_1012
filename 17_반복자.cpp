
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

// slist의 요소를 가르키기 위한 타입 - slist_iterator

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
  slist_iterator<T> end()   { return slist_iterator<T>(nullptr); }
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

template <typename T>
class xvector_iterator {
  T* current;
public:
  xvector_iterator(T* p) : current(p) {}

  T& operator*() { return *current; }
  xvector_iterator& operator++() { 
    ++current;
    return *this;
  }

  bool operator==(const xvector_iterator& t) { return current == t.current; }
  bool operator!=(const xvector_iterator& t) { return current != t.current; }
};


template <typename T>
class xvector {
  T* buff;
  int size;
public:
  using iterator = xvector_iterator<T>;

  xvector(int s) : size(s) { buff = new T[size]; }

  T& operator[](int index) { return buff[index]; }

  xvector_iterator<T> begin() { return buff; }
  xvector_iterator<T> end()   { return buff + size; }
};

#include <vector>

int main() {
  vector<int> x(3);
  x[0] = 10;
  x[1] = 20;
  x[2] = 30;

  // 위의 xvector가 아래의 코드가 동작할 수 있도록 만들어보세요.
  #if 1
  vector<int>::iterator iter = x.begin();

  while (iter != x.end()) {
    cout << *iter << endl;
    ++iter;
  }
  #endif
}


#if 0
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
#endif




// slist  - node<T>    
//   다음으로 이동: current = current->next;
// slist_iterator
//     ++ : current = current->next;



// vector - T* arr;
//   다음으로 이동: current += 1;
// vector_iterator
//    ++ : current += 1;

