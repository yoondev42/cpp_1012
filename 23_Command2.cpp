// 23_Command.cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

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

struct ICommand {
  virtual ~ICommand() {}

  virtual void Execute() = 0;

  virtual bool CanUndo() { return false; }
  virtual void Undo() {}
};

// 도형을 추가하는 명령은 로직이 거의 동일하다.
// AddCommand라는 부모를 도입해서, 공통된 로직을 캡슐화하자.
class AddCommand : public ICommand {
  vector<Shape*>& shapes;
public:
  AddCommand(vector<Shape*>& v) : shapes(v) {}


  bool CanUndo() override { return true; }

  void Undo() override {
    Shape* p = shapes.back();
    shapes.pop_back();
    delete p;
  }

  // 공통성과 가변성의 분리
  //  : 변하지 않는 부분은 부모가 제공하고, 변하는 부분은 자식이 가상함수를 통해 제공하는 설계 방법
  //  => Factory Method Pattern
  //    : Template Method Pattern의 모양인데, 자식이 재정의 하는 가상함수가
  //      알고리즘의 변경이 아닌, 객체 생성일 때

  void Execute() override final {
    shapes.push_back(CreateShape());
  }

  virtual Shape* CreateShape() = 0;
};


class AddRectCommand : public AddCommand {
public:
  AddRectCommand(vector<Shape*>& v) : AddCommand(v) {}

  // 아래 코드로 인해 부모의 Execute 는 수행되지 않습니다. - final 의도
  // void Execute() override {
  // }

  Shape* CreateShape() override {
    return new Rect;
  }
};

class AddCircleCommand : public AddCommand {
public:
  AddCircleCommand(vector<Shape*>& v) : AddCommand(v) {}

  Shape* CreateShape() override {
    return new Circle;
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

// 여러 명령을 묶는 매크로도 만들 수 있습니다.
class MacroCommand : public ICommand {
  vector<ICommand*> v;
public:
  void AddCommand(ICommand* p) { v.push_back(p); }

  void Execute() override {
    for (ICommand* p : v) {
      p->Execute();
    }
  }
};


int main() {
  vector<Shape*> shapes;
  stack<ICommand*> undo_stack;
  stack<ICommand*> redo_stack;

  MacroCommand* m = new MacroCommand;
  m->AddCommand(new AddRectCommand(shapes));
  m->AddCommand(new AddCircleCommand(shapes));
  m->AddCommand(new DrawCommand(shapes));
  m->Execute();

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
    else if (cmd == 3) {
      p = redo_stack.top();
      redo_stack.pop();
    }
    else if (cmd == 9) {
      p = new DrawCommand(shapes);
    }
    else if (cmd == 0) {
      p = undo_stack.top();
      undo_stack.pop();
      p->Undo();

      redo_stack.push(p); // !!!

      continue;
    }

    if (p) {
      p->Execute();

      if (p->CanUndo())
        undo_stack.push(p);
    }
  }
}