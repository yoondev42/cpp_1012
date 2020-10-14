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
