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

int main() {
  while (1) {
    int ch = getch();
    printf("%c\n", ch);
  }
}