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