// 23_Command.cpp
#include <iostream>
#include <vector>
#include <stack>
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
// 인터페이스
//   장점: 교체 가능한 유연한 디자인이 가능하다.
//   단점: 새로운 기능의 추가가 불편하다.
//        기본 구현을 제공하면, 하위 클래스가 새로운 기능을 추가하지 않아도 동작한다.
struct ICommand {
  virtual ~ICommand() {}

  virtual void Execute() = 0;

  virtual bool CanUndo() { return false; }
  virtual void Undo() {}
};

class AddRectCommand : public ICommand {
  vector<Shape*>& shapes;
public:
  AddRectCommand(vector<Shape*>& v) : shapes(v) {}

  void Execute() override {
    shapes.push_back(new Rect);
  }

  bool CanUndo() override { return true; }

  void Undo() override {
    Shape* p = shapes.back();
    shapes.pop_back();
    delete p;
  }
};

class AddCircleCommand : public ICommand {
  vector<Shape*>& shapes;
public:
  AddCircleCommand(vector<Shape*>& v) : shapes(v) {}

  void Execute() override {
    shapes.push_back(new Circle);
  }

  bool CanUndo() override { return true; }

  void Undo() override {
    Shape* p = shapes.back();
    shapes.pop_back();
    delete p;
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
  stack<ICommand*> undo_stack;

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
    else if (cmd == 0) {
      p = undo_stack.top();
      undo_stack.pop();

      if (p->CanUndo())
        p->Undo();
      continue;
    }

    if (p) {
      p->Execute();
      undo_stack.push(p);

    }
  }
}