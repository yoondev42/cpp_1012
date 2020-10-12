// 2_접근변경자.cpp

class Base {
private:
  int a;
protected:
  int b;
public:
  int c;
};

// 1. 부모의 private은 접근 변경자의 영향을 받지 않습니다.

// public 상속
//   Base       ->    Derived
//    public    ->     public
//    protected ->     protected

// protected 상속
//   Base       ->    Derived
//    public    ->     protected
//    protected ->     protected

// private 상속
//   Base       ->    Derived
//    public    ->     private
//    protected ->     private

class Derived : private Base {
               // 접근 변경자
};

// public 상속이 아닌 protected / private 상속
//  => 부모의 구현은 물려받지만, 인터페이스는 물려 받지 않겠다.

int main() {
  Base* p = new Derived;
  // Upcasting은 암묵적인 캐스팅이 허용됩니다.
  //  => 부모와 자식 클래스는 is-a 관계가 성립합니다.
  //  => Derived(Cat) is a Base(Animal)

  // Upcasting: public 상속에서만 허용됩니다.


  Base b;
  b.c = 10;

  Derived d;
  // d.c = 10;
  // d.b = 20; // protected X
}