
#include <iostream>
using namespace std;

// Bridge Pattern
//  구현부와 인터페이스를 분리해서
//  상호 독립적인 변경 / 확장을 편리하게 하자.


struct IMP3 {
  virtual ~IMP3() {}

  virtual void Play2() = 0;
  virtual void Stop2() = 0;
};


// 사용자가 IMP3의 구현부를 직접 사용하지 말고 중간층(Bridge, MP3)를
// 도입하면 상호의 변화에 쉽게 대응할 수 있다.
//  => Bridge Pattern
//     : (C++ pImpl Idiom)
//            pointer to implementation
class MP3 {
  IMP3* pImpl;
public:
  MP3(IMP3* p = nullptr) : pImpl(p) {
  }

  void Play() { pImpl->Play2(); }
  void Stop() { pImpl->Stop2(); }

  void PlayOneMinute() {
    
  }
};

class Person {
public:
  void PlayMusic(MP3* mp3) {
    // mp3의 PlayOneMinute()의 기능이 있었으면 한다.
    //   문제점: 인터페이스는 새로운 기능의 추가가 어렵다.
    mp3->Play();
    mp3->Stop();

    mp3->PlayOneMinute();
  }
};

class SmartPhone : public IMP3 {
public:
  void Play2() override {
    cout << "Play MP3 with SmartPhone" << endl;
  }

  void Stop2() override {
    cout << "Stop MP3 with SmartPhone" << endl;
  }
};

int main() {
  Person person;
  SmartPhone sp;
  MP3 mp3(&sp);

  person.PlayMusic(&mp3);
}