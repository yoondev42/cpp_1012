// State Pattern
#include <iostream>
using namespace std;


// "공통성과 가변성의 분리"
//  => 변하는 것과 변하지 않는 것은 분리되어야 한다.
//  디자인 패턴
//    1. 변하는 것(정책)을 가상함수로 분리한다.
//         Template Method Pattern
//         Factory Method Pattern

//    2. 변하는 것(정책)을 인터페이스 기반 클래스로 분리한다.
//         Staretegy Pattern
//         State Pattern


// 방법 3. 변하는 것을 인터페이스 기반 클래스로 뽑아낸다.
//     => State Pattern
//       : 구현하는 방법은 Starategy Pattern과 동일하다.
//         의도: 객체의 상태에 따라 동작을 변경하는 의도

// Item 상태에 따른 영웅의 동작을 정의한 인터페이스
struct IState {
  virtual ~IState() {}

  virtual void Run() = 0;
  virtual void Attack() = 0;
  // ...
};

class Hero {
  int gold;
  IState* state;
public:
  void SetState(IState* p) { state = p; }

  void Run()    { state->Run();     }
  void Attack() { state->Attack();  }
};

// 다양한 Item에 따른 동작을 정의한다.
class NormalState : public IState {
public:
  void Run() override {
    cout << "Hero Run" << endl;
  }

  void Attack() override {
    cout << "Hero Attack" << endl;
  }
};

class FastState : public IState {
public:
  void Run() override {
    cout << "Hero Fast Run" << endl;
  }

  void Attack() override {
    cout << "Hero Fast Attack" << endl;
  }
};

int main() {
  NormalState ns;
  FastState fs;

  Hero h;
  h.SetState(&ns);
  h.Run();

  h.SetState(&fs);
  h.Run();
}