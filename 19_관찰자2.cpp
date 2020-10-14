#include <vector>
#include <iostream>
using namespace std;


// 관찰자의 인터페이스
struct IObserver {
  virtual ~IObserver() {}

  virtual void onUpdate(int* data, int len) = 0;
};


// 관찰의 대상
//  - 관찰자 패턴에서 관찰의 대상(Subject)의 로직은 항상 동일하다.
//    부모 클래스를 통해 반복되는 로직을 제공해주자.



class Table {
  int data[5];
  vector<IObserver*> v;
public:
  Table() { memset(data, 0, sizeof data); }

  void attach(IObserver* p) {
    v.push_back(p);
  }

  void detach(IObserver* p) {}

  void notify() {
    for (IObserver* p : v) {
      p->onUpdate(data, 5);
    }
  }

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
  void onUpdate(int* data, int len) override {
    cout << "************ Pie ************" << endl;
    for (int i = 0 ; i < len; ++i)
      cout << i << ": " << data[i] << endl;
  }
};

class BarGraph : public IObserver {
public:
  void onUpdate(int* data, int len) override {
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
