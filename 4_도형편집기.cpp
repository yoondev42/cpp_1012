// 4_도형편집기.cpp

#include <iostream>
#include <vector>
using namespace std;

// 1. 모든 도형을 타입화 하면 편리하다.
// 2. 모든 도형의 공통의 부모가 있다면, 모든 도형을 묶어서 관리할 수 있다.
//    "A와 B를 묶기 위해서는 공통의 부모가 필요하다."

// 3. 모든 자식의 공통된 특징이 있다면, 반드시 부모에도 있어야 한다.
//    그래야 부모 포인터로 묶어서 사용할 때 해당 특징을 사용할 수 있다.
//    LSP(Liskov Substitution Principle)이라는 개념

// 4. 부모의 함수 중 자식이 재정의하는 모든 함수는 가상 함수 이어야 한다.
//    "가상함수가 아닌 함수는 재정의하지 말라" - Effecive C++

class Shape {
public:
  virtual ~Shape() {} 
  // 부모의 소멸자는 반드시 가상 이어야 한다.

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

int main() {
  vector<Shape*> shapes;

  while (1) {
    int cmd;
    cin >> cmd;

    if (cmd == 1) shapes.push_back(new Rect);
    else if (cmd == 2) shapes.push_back(new Circle);
    else if (cmd == 9) {
      for (Shape* e : shapes) {
        e->Draw();
      }
    }
  }
}