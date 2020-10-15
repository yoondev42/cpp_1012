// 23_Command.cpp
#include <iostream>
#include <vector>
using namespace std;

// Undo / Redo

// Undo: 동작을 스택을 통해 관리하자.
// Command Pattern: '명령을 객체로 추상화'한다.
//         => 스택에 저장하거나 불러오는 등의 기능을 구현하는 것이 가능하다.

class Shape {
public:
  virtual ~Shape() {} 

  virtual void Draw() { cout << "Shape draw" << endl; }
};

class Rect : public Shape {
public:
  void Draw() override { cout << "Rect draw" << endl; }
};

class Circle : public Shape {
public:
  void Draw() override { cout << "Circle draw" << endl; }
};


// 모든 명령을 객체화 - ICommand 도입
struct ICommand {
  virtual ~ICommand() {}

  virtual void Execute() = 0;
};

class AddRectCommand : public ICommand {
  vector<Shape*>& shapes;
public:
  AddRectCommand(vector<Shape*>& v) : shapes(v) {}

  void Execute() override {
    shapes.push_back(new Rect);
  }
};

class AddCircleCommand : public ICommand {
  vector<Shape*>& shapes;
public:
  AddCircleCommand(vector<Shape*>& v) : shapes(v) {}

  void Execute() override {
    shapes.push_back(new Circle);
  }
};

class DrawCommand : public ICommand {
  vector<Shape*>& shapes;
public:
  DrawCommand(vector<Shape*>& v) : shapes(v) {}

  void Execute() override {
    for (Shape* e : shapes) {
        e->Draw();
    }
  }
};


int main() {
  vector<Shape*> shapes;


  while (1) {
    ICommand* p = nullptr;
    int cmd;
    cin >> cmd;

    if (cmd == 1) {
      p = new AddRectCommand(shapes);
    } 
    else if (cmd == 2) {
      p = new AddCircleCommand(shapes);
    }
    else if (cmd == 9) {
      p = new DrawCommand(shapes);
    }

    if (p) {
      p->Execute();
    }
  }
}