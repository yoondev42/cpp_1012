// 12_CRTP.cpp

#include <iostream>
using namespace std;

// 가상 함수 기반의 이벤트 처리
//   문제점: 이벤트 종류(가상 함수의 개수)가 많아질수록, 메모리 오버헤드가 발생한다.
//   해결방법
//     1. 메세지맵
//       :  가상 함수는 1개만 정의한다.(자식 윈도우가 처리해야 하는 메세지와 핸들러를 배열로 만들어서 반환한다)
//     2. WTL(Windows Template Library) / ATL
//       => CRTP(Curiosly Recurring Template Pattern) - C++ Idioms
//         : 부모 클래스가 템플릿 인데 자식에서 템플릿 인자로 자신의 타입을 전달하는 기술
//           (Mix-in Template)
//            - 여러가지 활용이 가능한데, 아래 코드는 비가상함수를 가상함수처럼 동작하게 만드는 기법

template <typename T>
class Window {
public:
  void msgLoop() {
    
    static_cast<T*>(this)->onClick();
    // onClick();


    // this->onClick();
    // Window의 멤버 함수 안에서 this는 Window* 타입이다.
    //  : this의 타입을 자식 윈도우의 타입으로 캐스팅할 수 있다면,
    //    정적 바인딩을 통해서도 원하는 함수를 호출할 수 있다.
  }

  void onClick() { cout << "Window onClick" << endl; }
};

class MyWindow : public Window<MyWindow> {
public:
  void onClick() { cout << "MyWindow onClick" << endl; }
};

int main() {
  MyWindow w;
  w.msgLoop();
}

