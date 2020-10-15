// 힙에 만드는 싱글톤
#include <iostream>
#include <mutex>
using namespace std;

template <typename TYPE>
class Singleton {
protected:
  Singleton() {}
private:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static TYPE* sInstance;
  static mutex sMutex;
public:

  static TYPE& getInstance() {
    lock_guard<mutex> al(sMutex);

    if (sInstance == nullptr)
      sInstance = new TYPE;       // <----!!

    return *sInstance;
  }
};

template <typename TYPE>
TYPE* Singleton<TYPE>::sInstance = nullptr;

template <typename TYPE>
mutex Singleton<TYPE>::sMutex;

class Cursor : public Singleton<Cursor> {

};

int main() {
  auto& c1 = Cursor::getInstance();
  Cursor& c2 = Cursor::getInstance();

  printf("%p %p\n", &c1, &c2);
}
