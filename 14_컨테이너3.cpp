// 컨테이너 설계의 기술

#include <iostream>
using namespace std;

struct node {
  int data;
  node* next;

  node(int a, node* n) : data(a), next(n) {}
};

class slist {
  node* head;
public:
  slist() : head(nullptr) {}

  void push_front(int a) {
    head = new node(a, head);
  }

  int front() { return head->data; }
};

int main() {
  slist s;

  s.push_front(10);
  s.push_front(20);
  s.push_front(30);

  cout << s.front() << endl;
}