// 24_플라이웨이트.cpp
//  
#include <iostream>
#include <string>
using namespace std;

#include <thread>  // C++11 - sleep
                   // C++14 - user defined literal
                   

// #include <Windows.h>    Sleep(ms)
// #include <unistd.h>     sleep(seconds)

// Flyweight(경량) Pattern
// 의도: 속성이 동일한 객체가 다수 생성된다면, 하나의 객체의 '공유'해서 사용하자.

class Image {
  std::string url;
public:
  Image(const std::string& s) : url(s) {
    cout << "Loading from " << url << endl;
    // this_thread::sleep_for(chrono::duration<int>(2));
    this_thread::sleep_for(2000ms);
  }

  void draw() {
    cout << "Draw Image " << url << endl;
  }
};

int main() {
  Image* img1 = new Image("https://a.com/a.png");
  img1->draw();

  Image* img2 = new Image("https://a.com/a.png");
  img2->draw();
}