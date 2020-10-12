#include <termios.h>
#include <stdio.h>

int getch(void)
{
    int ch;

    struct termios old;
    struct termios newt;

    tcgetattr(0, &old);

    newt = old;
    newt.c_lflag &= ~(ICANON|ECHO);
    // newt.c_cc[VMIN] = 1;
    // newt.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &newt);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &old);

    return ch;
}

#include <iostream>
#include <string>
using namespace std;

// 공통성과 가변성을 분리하는 방법
// 1. 가상 함수
// 2. 인터페이스 기반 클래스로 분리한다.

// 방법 2.
//   변하는 정책을 인터페이스 기반의 다른 클래스로 뽑아낸다.
//   => 변경이 가능해야 하므로, 교체가 가능해야 한다.
//   => 약한 결합: 인터페이스 기반 클래스
//   => 전략 패턴(Strategy Pattern)


// Tempalte Method
// - 새로운 정책의 LineEdit가 필요하다면, LineEdit 기반의 클래스를 생성하고,
//    가상함수를 재정의합니다.

// Strategy
// - 새로운 정책이 필요하다면, IVadliator 인터페이스를 기반으로 정책 클래스를 만들고,
//   LineEdit의 setValidator를 통해 정책을 주입합니다.
// => 실행 시간에 정책을 교체하는 것이 가능합니다.
// => IValidator의 정책 클래스를 다른 종류의 클래스에서 재활용하는 것이 가능합니다.
//    : 정책의 재활용성이 좋습니다.

struct IValidator {
  virtual ~IValidator() {}

  virtual bool validate(const std::string& s, char c) = 0;
  virtual bool iscomplete(const std::string& s) = 0;
};

class LineEdit {
  string data;

  //-------------
  IValidator* pValidator;

public:
  LineEdit() : pValidator(nullptr) {}

  void setValidator(IValidator* p) { pValidator = p; }
  //-------------

  string getData() {
    data.clear();

    while (1) {
      char c = getch();
      
      if (c == 10 && (pValidator == nullptr || pValidator->iscomplete(data)))
        break;

      if (pValidator == nullptr || pValidator->validate(data, c)) {
        data.push_back(c);
        cout << c;
      }
    }

    cout << endl;
    return data;
  }
};

// 새로운 정책이 필요하면, IValidator 기반의 정책 클래스를 정의해서,
// LineEdit에 setValidator 해주면 됩니다.

// 5개의 숫자만 입력받아야 한다.
class LimitDigitValidator : public IValidator {
  int value;
public:
  LimitDigitValidator(int n) : value(n) {}

  bool validate(const std::string& s, char c) override {
    return s.size() < value && isdigit(c);
  }

  bool iscomplete(const std::string& s) override {
    return s.size() == value;
  }
};

int main() {
  LineEdit edit;
  LimitDigitValidator v(5);
  edit.setValidator(&v);

  while (1) {
    string s = edit.getData();
    cout << "Input: " << s << endl;
  }
}

//-----------------
// "요구사항의 변경"
// => 개발자 입장에서는 변경에 대한 방어적 설계를 고려해야 한다.
// 1) 변경을 예측하고, 이를 반영하여 설계 - Design for change
// 2) 변경에 쉽게 적응할 수 있도록 단순하게 설계
//   => 이후에 요구 사항의 변경이 발생했을 경우, 리팩토링을 통해 코드를 변경한다.

// 디자인 패턴 문제점
// => 복잡도

// 에릭감마 외 3명 - Gang of Four(4명의 깡패)

// 디자인 패턴 / 리팩토링
// - 디자인 패턴 마지막 장: 우리의 디자인 패턴은 리팩토링의 결과로 나온 구조를 반영한다.
//                   디자인 패턴은 리팩토링의 목표점이 된다.
// - 리팩토링 서문: 패턴과 리팩토링은 자연스러운 관계가 있다. 패턴은 도달하고 싶은 곳이고, 리팩토링은 그곳으로 가는 방법이다.