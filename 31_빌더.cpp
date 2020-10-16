// 31_빌더.cpp

#include <string>
#include <iostream>
using namespace std;

// 디자인 패턴에서 변하는 것을 '인터페이스 기반의 클래스로 만들어서 교체'하는 패턴은 3가지 입니다.
// 1. Strategy Pattern
//       : 알고리즘을 캡슐화해서 실행 시간에 교체 가능하게 하는 것
//        => LineEdit - IValidator
//           SetValidator(&v);

// 2. State Pattern
//       : 객체의 상태에 따른 동작을 정의한 클래스를 만들어서 교체하는 것
//       => Hero   -  IState
//          SetState(&s);

// 3. Builder Pattern
//       : 동일한 구축 공정으로 객체를 만들지만, 각 공정에 따른 표현이 달라지는 객체를 만들 때
//       => Director - IBuilder
//          SetBuilder(&b);

// 실행시간에 교체가 필요해야 한다.
//   => 인터페이스 기반 클래스를 통해 설계


// 축구 게임을 만들자.
//  - 캐릭터 커스터마이제이션
//   : 동일한 구축 공정을 사용하지만 각 공정에 따라 표현이 달라지는 객체를 만들 때
//    => 빌더 패턴

using Player = std::string;

struct IBuilder {
  virtual ~IBuilder() {}

  virtual void MakeFace() = 0;
  virtual void MakeUniform() = 0;
  virtual void MakeShoes() = 0;

  virtual Player Build() = 0;
};

// 변하지 않는 구축 공정
class Director {
  IBuilder* pBuilder;
public:
  Director() : pBuilder(nullptr) {}

  void SetBuilder(IBuilder* p) { pBuilder = p; }
  Player Construct() {
    // 1. 얼굴
    pBuilder->MakeFace();
    // 2. 몸통
    pBuilder->MakeUniform();
    // 3. 신발
    pBuilder->MakeShoes();
    return pBuilder->Build();
  }
};

// 다양한 나라의 빌더를 제공합니다.
class KoreanBuilder : public IBuilder {
  Player player;
public:
  void MakeFace()  override {
    player += "삿갓";
  }

  void MakeUniform() override {
    player += "한복";
  }

  void MakeShoes()  override {
    player += "짚신";
  }

  Player Build() override {
    return player;
  }
};

class EnglandBuilder : public IBuilder {
 Player player;
public:
  void MakeFace()  override {
    player += "노란머리";
  }

  void MakeUniform() override {
    player += "양복";
  }

  void MakeShoes()  override {
    player += "구두";
  }

  Player Build() override {
    return player;
  }
};

int main() {
  KoreanBuilder kb;
  EnglandBuilder eb;

  Director d;
  d.SetBuilder(&kb);
  Player c1 = d.Construct();
  cout << c1 << endl;

  d.SetBuilder(&eb);
  Player c2 = d.Construct();
  cout << c2 << endl;
}