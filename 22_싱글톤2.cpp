// 힙에 만드는 싱글톤
#include <iostream>
using namespace std;

class Cursor {
private:
  Cursor() {}
  Cursor(const Cursor&) = delete;
  Cursor& operator=(const Cursor&) = delete;

  static Cursor* sInstance;
public:
  static Cursor& getInstance() {
    if (sInstance == nullptr)
      sInstance = new Cursor;

    return *sInstance;
  }
};

Cursor* Cursor::sInstance = nullptr;

int main() {
  auto& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  printf("%p %p\n", &c1, &c2);
}
