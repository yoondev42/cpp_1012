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
};

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