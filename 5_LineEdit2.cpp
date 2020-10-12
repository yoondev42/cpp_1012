// 5_LineEdit.cpp
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

// GUI 도구인 Edit 박스(LineEdit, EditText)를 만들어봅시다.
#include <iostream>
#include <string>
using namespace std;

// 1. Validation의 정책은 변경이 가능해야 합니다.
//   방법 1.
//    => 변하는 것을 가상함수화 한다. - template method pattern
//     : 변하지 않는 코드(공통성)에서 변해야 하는 것(가변성)이 있다면
//       변하는 것을 가상함수로 뽑아낸다.
class LineEdit {
  string data;
public:
  virtual bool validate(char c) { return isdigit(c); }

  string getData() {
    data.clear();

    while (1) {
      char c = getch();
      
      if (c == 10)
        break;

      if (validate(c)) {
        data.push_back(c);
        cout << c;
      }
    }

    cout << endl;
    return data;
  }
};

// 이제 정책을 변경하고 싶다면 파생 클래스에서 가상 함수를 재정의하면 됩니다.
class AddressLineEdit : public LineEdit {
public:
  bool validate(char c) override {
    return true;
  }
};

int main() {
  // LineEdit edit;
  AddressLineEdit edit;
  while (1) {
    string s = edit.getData();
    cout << "Input: " << s << endl;
  }
}