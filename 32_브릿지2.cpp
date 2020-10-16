
#include <iostream>
using namespace std;

struct IMP3 {
  virtual ~IMP3() {}

  virtual void Play() = 0;
  virtual void Stop() = 0;

  // virtual void PlayOneMinute() = 0;
};

class Person {
public:
  void PlayMusic(IMP3* mp3) {
    // mp3의 PlayOneMinute()의 기능이 있었으면 한다.
    //   문제점: 인터페이스는 새로운 기능의 추가가 어렵다.
    mp3->Play();
    mp3->Stop();
  }
};

class SmartPhone : public IMP3 {
public:
  void Play() override {
    cout << "Play MP3 with SmartPhone" << endl;
  }

  void Stop() override {
    cout << "Stop MP3 with SmartPhone" << endl;
  }
};

int main() {
  Person person;
  SmartPhone mp3;

  person.PlayMusic(&mp3);
}