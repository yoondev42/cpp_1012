// 24_플라이웨이트.cpp
//  Flyweight(경량) Pattern
#include <iostream>
#include <string>
#include <map>
#include <thread>
using namespace std;

// 1) Factory Class

// 방법 2
//   static factory method 형식으로 구현하자.
//   => 싱글톤 공장 클래스를 사용하지 않아도, 동일한 목적을 달성할 수 있다.

class Image {
private:
  std::string url;
  static map<std::string, Image*> cache;

  Image(const std::string& s) : url(s) {
    cout << "Loading from " << url << endl;
    // this_thread::sleep_for(chrono::duration<int>(2));
    this_thread::sleep_for(2000ms);
  }
public:
  static Image* createImage(const std::string& url) {
    if (cache[url] == nullptr)
      cache[url] = new Image(url);
    return cache[url];
  }

  void draw() {
    cout << "Draw Image " << url << endl;
  }
};

map<std::string, Image*> Image::cache;

#if 1
int main() {
  Image* img1 = Image::createImage("https://a.com/a.png");
  img1->draw();

  Image* img2 = Image::createImage("https://a.com/a.png");
  img2->draw();
}
#endif

// C++에서 객체 복사
// 1. 깊은 복사 
// 2. 참조 계수
// 3. 복사 금지
// 4. 소유권 이전

class Sample {
public:
  Sample() {}

  void foo() {
    Sample s1;
    Sample s2;
    // Sample s2 = s1;
    // s2 = s1;
  }

private:
  // 복사/대입 금지
  Sample(const Sample&) = delete;
  Sample& operator=(const Sample&) = delete;
};

#if 0
int main() {
  Sample s1;
  s1.foo();

  // Sample s2 = s1;  // !
}
#endif