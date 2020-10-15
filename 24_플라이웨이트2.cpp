#include <iostream>
#include <string>
#include <thread>  
#include <map>
using namespace std;

// 의도: 속성이 동일한 객체가 다수 생성된다면, 하나의 객체의 '공유'해서 사용하자.
//     => '캐시'를 도입하자.

// 방법 1.
//   Image를 직접 생성하는 것이 아니라, Image 객체를 생성하는 역활을 담당하는 객체를 도입하자.

class Image {
private:
  std::string url;

  Image(const std::string& s) : url(s) {
    cout << "Loading from " << url << endl;
    // this_thread::sleep_for(chrono::duration<int>(2));
    this_thread::sleep_for(2000ms);
  }
public:
  void draw() {
    cout << "Draw Image " << url << endl;
  }

  friend class ImageFactory;
};

// Image 객체를 다양한 방법으로 생성하기 위한 기능을 모아놓은 클래스
//   Factory: '생성'

// 1. 공장(Factory) class: 객체 생성을 한곳에서 중앙집중적으로 관리하는 것이 가능하다.
// 2. 공장은 싱글톤으로 만드는 경우가 많습니다.
class ImageFactory {
private:
  map<string, Image*> cache;

  ImageFactory() {}

  ImageFactory(const ImageFactory&) = delete;
  ImageFactory& operator=(const ImageFactory&) = delete;
public:
  static ImageFactory& getInstance() {
    static ImageFactory instance;
    return instance;
  }

  // Image를 생성하는 아래의 함수를 변경한다면,
  // 전체 코드를 수정하지 않고 객체 생성의 정책을 변경하는 것이 가능하다.
  Image* createImage(const std::string& url) {
    if (cache[url] == nullptr) {
      cache[url] = new Image(url);
    }

    return cache[url];
  }
};


int main() {
  Image* img1 = ImageFactory::getInstance().createImage("https://a.com/a.png");
  img1->draw();

  Image* img2 = ImageFactory::getInstance().createImage("https://a.com/b.png");
  img2->draw();
}