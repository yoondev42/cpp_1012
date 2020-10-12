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

// 5. 새로운 기능이 추가되어도, 기존 코드는 수정되면 안된다.
//    OCP(Open Close Principle)
//    => 기능 확장에는 열려 있고, 수정에는 닫혀 있어야 한다.

// 6. Prototype Pattern: 기존의 존재하는 객체를 기반으로 새로운 객체를 생성하는 패턴
//    => "다형성"을 이용해서 새로운 객체를 생성한다.
//       Java, C#: Clone()
//     Swift/ObjC: copy()

// 7. 리팩토링(마틴 파울러): 유지보수가 불가능한 나쁜 코드를 유지 보수가 가능한 코드로 변경하는 작업
//     "기존 코드의 동작을 변경하지 않고 구조를 개선하는 작업"
//    => Replace type code with Polymorphism


class Shape {
  // int type;  // 0: Rect / 1: Circle
public:
  virtual ~Shape() {} 
  // 부모의 소멸자는 반드시 가상 이어야 한다.

  virtual void Draw() { cout << "Shape draw" << endl; }
  virtual Shape* Clone() {
    return new Shape(*this);
  }
};

class Rect : public Shape {
public:
  void Draw() override { cout << "Rect draw" << endl; }

  // 공변 반환의 법칙: 부모의 함수를 오버라이딩 할때, 반환 타입을 하위 타입으로 지정하는 것을 허용한다.
  // => Template
  // => 더 이상 Clone을 통해 생성된 객체를 이용할 때, 다운 캐스팅이 필요하지 않다.
  Rect* Clone() override {
    return new Rect(*this);
  }
};

class Circle : public Shape {
public:
  void Draw() override { cout << "Circle draw" << endl; }

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


      // k번째 도형의 복사본을 만들어서 shapes에 추가한다.
      shapes.push_back(shapes[k]->Clone());

      // k번째 도형은 Rect? Circle? - RTTI를 이용하면, 타입의 정보를 실행시간에 확인할 수 있습니다.
      // => 아래의 코드는 OCP를 만족하지 않는다.
      //    새로운 도형이 추가될 때마다, 아래 코드는 수정되어야 한다.
      #if 0
      Shape* p = shapes[k];
      if (typeid(*p) == typeid(Rect)) {
        cout << "Rect" << endl;
      } else if (typeid(*p) == typeid(Circle)) {
        cout << "Circle" << endl;
      }
      #endif

    }
    else if (cmd == 9) {
      // 다형성은 OCP를 만족한다.
      for (Shape* e : shapes) {
        e->Draw();
      }
    }
  }
}