// 매크로 - 텍스트 치환
#include <stdio.h>

// 매크로 이름 규칙
//  - 대문자_
//    PI, ADD_XXX(x)

// 매크로
#define PI 3.14

// 매크로 함수
#define POW(x) x * x

#if 0
void log(const char* message) {
  printf("%s:%d] %s\n", __func__, __LINE__, message);
}
#endif

void log(const char* func, int line, const char* message) {
  printf("%s:%d] %s\n", func, line, message);
}

#define LOG(message) log(__func__, __LINE__, message)

int main() {
  LOG("hello world");
  LOG("program end");

  // log(__func__, __LINE__, "hello world");
  // log(__func__, __LINE__, "program end");

  // log("hello, world");  // main:19
  // log("program exit");

  // printf("%lf\n", PI);
  // printf("%d\n", POW(2));
}