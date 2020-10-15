#include <iostream>
using namespace std;

// 객체의 수명을 참조 계수 기반으로 관리하자.

class Image {
  int mCount;
public:
  Image() : mCount(0) {}
  ~Image() { cout << "Image 파괴" << endl; }

  void addRef()  { ++mCount; }
  void release() {
    if (--mCount == 0)
      delete this;
  }

  void draw() {
    cout << "Image draw" << endl;
  }
};

// Image*를 바로 사용하면, 참조계수를 직접 관리해야 한다.
// 불편하므로 참조 계수를 자동으로 관리하는 클래스
// Proxy Pattern: 대리자
//             => 기존 요소를 대신하는 클래스
//             => 클래스 이므로, 생성, 파괴, 복사, 대입 등의 모든 과정에 추가적인 작업을 수행할 수 있다.
class ImageProxy {
  Image* obj;
public:
  // 규칙 1. 객체를 만들면 참조 계수 증가
  ImageProxy(Image* p) : obj(p) { obj->addRef(); }

  // 규칙 3. 객체 포인터 사용 후, 참조 계수 감소
  ~ImageProxy() {  obj->release();  }

  // 규칙 2. 객체 포인터를 복사하면, 참조 계수 증가
  ImageProxy(const ImageProxy& p) : obj(p.obj) {
    obj->addRef();
  }

  // 진짜 Image* 처럼 사용할 수 있어야 한다.
  Image* operator->() { return obj; }
  Image& operator*() { return *obj; }
};

int main() {
  ImageProxy p1(new Image);
  ImageProxy p2 = p1;

  p1->draw();
  (*p2).draw();
}


#if 0
int main() {
  // 규칙 1. 객체를 만들면 참조 계수 증가
  ImageProxy p1(new Image);
  // Image* p1 = new Image;
  // p1->addRef();

  // 규칙 2. 객체 포인터를 복사하면, 참조 계수 증가
  ImageProxy p2 = p1;
  // Image* p2 = p1;
  // p2->addRef();
  
  // 규칙 3. 객체 포인터 사용 후, 참조 계수 감소
  // p2->release();
  // p1->release();
}
#endif

#if 0
int main() {
  // 규칙 1. 객체를 만들면 참조 계수 증가
  Image* p1 = new Image;
  p1->addRef();

  // 규칙 2. 객체 포인터를 복사하면, 참조 계수 증가
  Image* p2 = p1;
  p2->addRef();
  
  // 규칙 3. 객체 포인터 사용 후, 참조 계수 감소
  p2->release();
  p1->release();
}
#endif