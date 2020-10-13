// 컨테이너 설계의 기술

#include <iostream>
using namespace std;

// 2. Template 기반 컨테이너

template <typename T>
struct node {
  T data;
  node* next;

  node(const T& a, node* n) : data(a), next(n) {}
};

template <typename T>
class slist {
  node<T>* head;
public:
  slist() : head(nullptr) {}

  void push_front(const T& a) {
    head = new node<T>(a, head);
  }

  const T& front() { return head->data; }
};

#include <list>

// 장점: 타입 안정성이 뛰어나고, 객체 뿐 아니라 표준 타입도 저장이 가능하고,
//      꺼낼 때 캐스팅도 필요 없다.
// 단점: 템플릿 이므로, 여러 가지 타입에 대해서 사용한다면 list의 기계어 코드가 많아진다.
//      코드 메모리 오버헤드가 있다.

class Rect {};

int main() {
  slist<int> s;

  s.push_front(10);
  s.push_front(20);
  s.push_front(30);
  // s.push_front(new Rect);

  int n = s.front();
  cout << s.front() << endl;
}