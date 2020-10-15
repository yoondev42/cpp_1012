
#include <iostream>
using namespace std;

#include <functional>
// function/ bind의 사용법

// void (*p)();
void foo() { printf("foo\n"); }
void goo(int a) { printf("goo - %d\n", a); }

void hoo(int a, int b) { printf("hoo - %d %d\n", a, b); }
void koo(int a, int b, int c, int d) { printf("koo - %d %d %d %d\n", a, b, c, d); }

using namespace std::placeholders;

class Dialog {
public:
  void f1() { cout << "f1" << endl; }
  void f2(int a) { cout << "f2" << endl; }
};

// Dialog
//   f1 - void(Dialog*)
//   f2 - void(Dialog*, int)

int main() {
  Dialog dlg;
  function<void(Dialog*)> fp;
  fp = &Dialog::f1;
  fp(&dlg);

  function<void(Dialog*,int)> fp2;
  fp2 = &Dialog::f2;
  fp2(&dlg, 42);
}



#if 0
int main() {
  function<void(int, int)> fp;
  fp = &hoo;
  fp(10, 20);

  fp = bind(&koo, _1, _2, _2, _1);
  fp(10, 30);
  // 10 30 30 10
}
#endif

#if 0
int main() {
  function<void(int)> fp;
  fp = &goo;
  fp = bind(&hoo, 30, _1);
  
  // koo를 호출할 때
  fp = bind(&koo, _1, _1, 10, _1);
  
  fp(20);
  // fp(20) -> koo - 20, 20, 10, 20
  // fp(30) -> koo - 30, 30, 10, 30
}
#endif

#if 0
int main() {
  // void (*fp)() = &foo;
  function<void()> fp = &foo;
  fp();

  // goo(20);
  fp = bind(&goo, 20);
  fp();

  fp = bind(&hoo, 10, 20);
  fp();

  fp = bind(&koo, 10, 20, 30, 40);
  fp();
}
#endif