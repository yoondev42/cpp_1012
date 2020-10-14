
#include <iostream>
using namespace std;

// 인터페이스 기반 반복자 설계
//    Java, C# 



template <typename T>
struct node {
  T data;
  node* next;

  node(const T& a, node* n) : data(a), next(n) {}
};


// 1. 인터페이스를 약속합니다.
template <typename T>
struct Iterator {
  virtual ~Iterator() {}

  // 현재 위치의 값을 반환하고, 다음 위치로 이동하는 함수
  virtual T next() = 0;

  // 다음 위치로 이동할 수 있는지를 확인하는 함수
  virtual bool hasNext() = 0;
};

template <typename T>
class slist_iterator : public Iterator<T> {
  node<T>* current;
public:
  slist_iterator(node<T>* p) : current(p) {}

  T next() override {
    T value = current->data;
    current = current->next;
    
    return value;
  }

  bool hasNext() override {
    return current != nullptr;
  }
};


// 2. 컨테이너를 통해서 반복자를 꺼낼 수 있는 인터페이스가 약속되어 있습니다.
template <typename T>
struct Iterable {
  virtual ~Iterable() {}

  virtual Iterator<T>* iterator() = 0;
};

template <typename T>
class slist : public Iterable<T> {
  node<T>* head;
public:
  
  Iterator<T>* iterator() override {
    return new slist_iterator<T>(head);
  }

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

  Iterator<int>* iter = s.iterator();
  while (iter->hasNext()) {
    cout << iter->next() << endl;
  }
}

//              C++ Iterator            Java Interator
//  인터페이스   암묵적(연산자 오버로딩)       명시적인 인터페이스 타입을 약속(Iterator)
// 반복자 얻기   암묵적(begin / end)       명시적인 인터페이스 타입을 약속(Iterable)


// find          <algorithm>           각각의 컨테이너가 메소드를 통해 구현
//            C++의 반복자를 만족하면,           알고리즘 함수를 이용 X
//            C++이 제공하는 알고리즘 함수를 
//              이용하는 것이 가능하다.
