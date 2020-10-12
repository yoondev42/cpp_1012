// 5_LineEdit.cpp

// #include <conio.h>
//    getch

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
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &newt);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &old);

    return ch;
}

// #include <conio.h>
// int main() {
//   while (1) {
//     int ch = getch();
//     printf("%c\n", ch);
//   }
// }

//---------------------------------
// GUI 도구인 Edit 박스(LineEdit, EditText)를 만들어봅시다.
#include <iostream>
#include <string>
using namespace std;

class LineEdit {
  string data;
public:
  string getData() {
    data.clear();

    while (1) {
      char c = getch();
      
      if (c == 13)  // enter
        break;

      if (isdigit(c)) {
        data.push_back(c);
        cout << c;
      }
    }

    cout << endl;
    return data;
  }
};

int main() {
  LineEdit edit;
  while (1) {
    string s = edit.getData();
    cout << "Input: " << s << endl;
  }
}