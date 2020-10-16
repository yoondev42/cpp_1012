// 추상 팩토리
#include <iostream>
using namespace std;

// Abstract Factory Pattern
//  의도: 추상적인 부품을 조합해서 추상적인 제품을 만든다.
//   => 공장도 인터페이스 기반으로 설계해서, 교체 가능하도록 만들자.

// - GUI Framework를 설계해보자.
//   = 프로그램의 명령행 인자에 따라서, 다른 테마를 적용하고 싶다.

struct IButton {
  virtual void draw() = 0;
};
class WindowsButton : public IButton {
public:
  void draw() {
    cout << "Draw Windows Button" << endl;
  }
};
class LinuxButton : public IButton {
public:
  void draw() {
    cout << "Draw Linux Button" << endl;
  }
};

struct IEdit {};
class WindowsEdit : public IEdit {};
class LinuxEdit : public IEdit {};

struct IFactory {
  virtual IButton* createButton() = 0;
  virtual IEdit* createEdit() = 0;
};

class WindowsFactory : public IFactory {
public:
  WindowsButton* createButton() {
    return new WindowsButton;
  }
  WindowsEdit* createEdit() {
    return new WindowsEdit;
  }
  //...
};

class LinuxFactory : public IFactory {
public:
  LinuxButton* createButton() {
    return new LinuxButton;
  }
  LinuxEdit* createEdit() {
    return new LinuxEdit;
  }
  //...
};


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: ./a.out [--windows|--linux]\n");
    return 1;
  }

  IFactory* factory;
  if (strcmp(argv[1], "--windows") == 0) {
    printf("Windows theme\n");
    factory = new WindowsFactory;

  } else if (strcmp(argv[1], "--linux") == 0) {
    printf("Linux theme\n");
    factory = new LinuxFactory;
  }

  IButton* button = factory->createButton();
  button->draw();
}

#if 0
int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: ./a.out [--windows|--linux]\n");
    return 1;
  }

  IButton* button;
  IEdit* edit;
  //...
  if (strcmp(argv[1], "--windows") == 0) {
    printf("Windows theme\n");
    button = new WindowsButton;
    edit = new WindowsEdit;
    //...

  } else if (strcmp(argv[1], "--linux") == 0) {
    printf("Linux theme\n");

    button = new LinuxButton;
    edit = new LinuxEdit;
    //...



  }
}
#endif

#if 0
int main(int argc, char** argv) {
  // $ ./a.out --windows
  //  argv[0]: ./a.out
  //  argv[1]: --windows

  // $ ./a.out --linux
  //  argv[0]: ./a.out
  //  argv[1]: --linux 
  if (argc != 2) {
    printf("Usage: ./a.out [--windows|--linux]\n");
    return 1;
  }

  if (strcmp(argv[1], "--windows") == 0) {
    printf("Windows theme\n");
  } else if (strcmp(argv[1], "--linux") == 0) {
    printf("Linux theme\n");
  }
}
#endif
#if 0
int main(int argc, char** argv) {
  printf("argc: %d\n", argc);

  for (int i = 0 ; i < argc ; ++i) {
    printf("%s\n", argv[i]);
  }
}
#endif