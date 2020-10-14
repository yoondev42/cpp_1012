#include <vector>
#include <iostream>
using namespace std;


// 관찰자의 인터페이스
class Subject;
struct IObserver {
  virtual ~IObserver() {}

  Subject* pSubject;
  virtual void onUpdate() = 0;
};


// 관찰의 대상
//  - 관찰자 패턴에서 관찰의 대상(Subject)의 로직은 항상 동일하다.
//    부모 클래스를 통해 반복되는 로직을 제공해주자.

class Subject {
  vector<IObserver*> v;
public:
  virtual ~Subject() {}

  void attach(IObserver* p) {
    v.push_back(p);
    p->pSubject = this;
  }

  void detach(IObserver* p) {}
  
  void notify() {
    for (IObserver* p : v) {
      p->onUpdate();
    }
  }
};

class Table : public Subject {
  int data[5];
public:
  Table() { memset(data, 0, sizeof data); }

  const int* getData() const { return data; }
  int getSize() const { return 5; }

  void edit() {
    while (1) {
      int index;
      cout << "index: ";  cin >> index;
      cout << "data: "; cin >> data[index];

      notify();
    }
  }
};

//---------
class PieGraph : public IObserver {
public:
  void onUpdate() override {
    // Table* table = dynamic_cast<Table*>(pSubject);
    // if (table != 0) {}
    Table* table = static_cast<Table*>(pSubject);
    // 다운 캐스팅을 수행할 때, 해당 타입에 대해서 확신할 수 있다면,
    // static_cast를 사용하는 것이 좋다.
    // => 런타임 오버헤드가 존재하지 않는다.
    const int* data = table->getData();
    int len = table->getSize();

    cout << "************ Pie ************" << endl;
    for (int i = 0 ; i < len; ++i)
      cout << i << ": " << data[i] << endl;
  }
};

class BarGraph : public IObserver {
public:
  void onUpdate() override {
    Table* table = static_cast<Table*>(pSubject);
    const int* data = table->getData();
    int len = table->getSize();

    cout << "************ Bar ************" << endl;
    for (int i = 0 ; i < len; ++i)
      cout << i << ": " << data[i] << endl;
  }
};

int main() {
  Table table;
  PieGraph pg;
  BarGraph bg;

  table.attach(&pg);
  table.attach(&bg);

  table.edit();
}

//------------------------------------
// 플러그인 원리
// 1. 플러그인의 개발자는 자신이 만든 그래프를 동적 라이브러리의 형태로 제공한다.
// 2. 플러그인을 설치하면 약속된 디렉토리에 저장한다.
// 3. 프로그램을 다시 컴파일 하지 않아도, 자동으로 그래프가 추가되도록 한다.

// 라이브러리
// 1. 정적 라이브러리
//    Linux     Windows
//     .a         .lib

// - 실행 파일을 만들 때 모든 구현이 실행파일에 포함된다.
// - 라이브러리가 변경될때마다 실행 파일을 다시 컴파일 해야 한다.
// - 배포가 쉽다.
//   바이너리 하나로 모든 것을 수행할 수 있다.

// 2. 동적 라이브러리
//    Linux     Windows
//     .so        .dll
// - 실행 파일에 라이브러리의 정보만 포함한다.
// - 실행 파일이 실행될 때, 라이브러리를 로드해서, 실행한다.
// - 라이브러리가 변경되면, 실행 파일을 다시 컴파일 할 필요가 없다.
// - 배포가 어렵다.
//   바이너리 뿐 아니라 의존하는 모든 동적라이브러리에 대한 설치가 필요하다.(인스톨러)


// main.cpp  -> main.o -> a.out

// hello.cpp -> hello.o -> libhello.a 
//                         => ar rcv libhello.a hello.o
//                         libhello.so
//                         라이브러리가 제공하는 함수에 대한 헤더파일도 같이 제공하는 것이 좋습니다.