// 컨테이너 설계의 기술
#include <iostream>
using namespace std;

// 템플릿 기반의 컨테이너는 메모리 오버헤드가 있다.
// 메모리 부족한 환경에서는 적절하지 않을 수 있다.
// => Android Framework 내부의 컨테이너는 아래와 같은 기술을 사용하고 있습니다.

// 1. 데이터를 void* 기반으로 저장합니다.
//    1) void*는 모든 포인터 타입을 저장할 수 있다.
//    2) void*를 실제 타입으로 변환하기 위해서는 반드시 명시적인 캐스팅이 필요하다.


struct node {
  void* data;
  node* next;

  node(void* a, node* n) : data(a), next(n) {}
};

class slistImpl {
  node* head;
public:
  slistImpl() : head(nullptr) {}

  void push_front(void* a) {
    head = new node(a, head);
  }

  void* front() { return head->data; }
};

// 위의 구현을 이용하는 템플릿 인터페이스를 만들자. - Adapter Pattern
//  => 인라인 치환 후, 인라인 함수가 호출되지 않을 때는 코드 메모리 영역에서 사라진다.
//     : 코드 메모리 오버헤드가 존재하지 않는다.
//     -> Thin Template
template <typename T> class slist : private slistImpl {
public:
  inline void push_front(const T& a) {
    //  a - const T&
    // &a - const T*
    // const_cast<T*>(&a) - T*

    slistImpl::push_front(const_cast<T*>(&a));
  }

  inline T& front() {
    return *(static_cast<T*>(slistImpl::front()));
  }
};


#if 0
int main() {
  slist<int> s;

  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  int n = s.front();
  cout << n << endl;
}
#endif

// 컨테이너 설계 기술 3가지
// 1. object* 
// 2. Template
// 3. Thin Template

// Design Pattern
// 1. Adapter Pattern
// 2. Prototype Pattern
// 3. Template Method Pattern
// 4. Strategy Pattern
// 5. Composite Pattern




// Upcasting
// Downcasting

class Animal {
public:
  virtual ~Animal() {}
};

class Dog : public Animal {

};

// 부모의 포인터 타입은 자식 객체의 주소를 담을 수 있다.
//  => 자식의 포인터 타입은 부모의 포인터 타입으로 암묵적인 캐스팅은 허용한다.  - Upcasting

//  => 부모의 포인터 타입을 자식의 포인터 타입으로 변환하기 위해서는 명시적인 캐스팅이 필요하다.  - Downcating

int main() {
  Animal* p = new Dog;  // ?

  Dog* p2 = dynamic_cast<Dog*>(p);
}