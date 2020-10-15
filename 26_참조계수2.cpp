#include <iostream>
using namespace std;

class RefCountedObject {
  int mCount;
public:
  RefCountedObject() : mCount(0) {}
  virtual ~RefCountedObject() { cout << "RefCountedObject 파괴" << endl; }

  void addRef()  { ++mCount; }
  void release() {
    if (--mCount == 0)
      delete this;
  }
};

class Image : public RefCountedObject {
public:
  void draw() {}
};

template <typename T>
class sp {
  T* obj;
public:
  inline sp(T* p) : obj(p) { obj->addRef(); }
  inline ~sp() {  obj->release();  }

  inline sp(const sp& p) : obj(p.obj) {
    obj->addRef();
  }

  inline T* operator->() { return obj; }
  inline T& operator*() { return *obj; }
};

int main() {
  sp<Image> p1(new Image);
  sp<Image> p2 = p1;

  p1->draw();
}