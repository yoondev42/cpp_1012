#include <iostream>
#include <vector>
using namespace std;

// 화면에 출력하는 기능은, 반드시 스레드 안전하게 동작해야 합니다.
// => '동기화 객체'를 이용해서, 화면에 출력하는 코드에 대해서 동기화를 수행해주어야 합니다.
//     Mutex

// 8. Template Method Pattern
//    => 변하지 않는 전체 알고리즘은 부모가 비가상함수로 제공하고,
//       변해야 하는 부분만 가상함수화해서 자식이 변경할 수 있게 하는 디자인 기법


#include <mutex>

std::mutex m;

class Shape {
public:
  virtual ~Shape() {} 

  // 공통성과 가변성을 분리하는 방법
  //  1. 변하지 않는 부분은 부모가 비 가상함수로 정의하고,
  //     변하는 부분은 가상함수를 통해 자식이 재정의할 수 있도록 한다.
  //     => 변하는 것을 가상함수로 분리한다.
  //     => Template Method Pattern
  void Draw() { 
    m.lock();
    DrawImpl();
    m.unlock();
  }

  virtual Shape* Clone() {
    return new Shape(*this);
  }

protected:
  virtual void DrawImpl() {
    cout << "Shape draw" << endl;
  }

};

class Rect : public Shape {
public:
  void DrawImpl() override {
    cout << "Rect draw" << endl; 
  }

  Rect* Clone() override {
    return new Rect(*this);
  }
};

class Circle : public Shape {
public:
  void DrawImpl() override {
    cout << "Circle draw" << endl; 
  }

  Circle* Clone() override {
    return new Circle(*this);
  }
};

int main() {
  vector<Shape*> shapes;

  while (1) {
    int cmd;
    cin >> cmd;

    if (cmd == 1) shapes.push_back(new Rect);
    else if (cmd == 2) shapes.push_back(new Circle);
    else if (cmd == 8) {
      cout << "몇번째 도형을 복제할까요? >> ";
      int k;
      cin >> k;
    }
    else if (cmd == 9) {
      // 다형성은 OCP를 만족한다.
      for (Shape* e : shapes) {
        e->Draw();
      }
    }
  }
}