
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

int main() {
  function<void(int)> fp;
  fp = &goo;
  fp = bind(&hoo, 30, _1);


  fp(10);
}


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