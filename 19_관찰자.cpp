
#include <vector>
#include <iostream>
using namespace std;

// 관찰자(Observer) 패턴: 하나의 이벤트를 등록된 객체에게 '전파'하는 패턴(브로드캐스트)
//   : 매우 중요합니다.
// => 비동기 이벤트의 처리

// Subject가 변경되었을 때, Graph가 반응하기 위해서의 설계 방법 2가지
//  1. poll
//    => 불필요한 리소스의 소모가 있다.

//  2. push
//    => 불필요한 리소스의 소모가 없다.

// 관찰자의 인터페이스
struct IObserver {
  virtual ~IObserver() {}

  virtual void onUpdate(int* data, int len) = 0;
};


// 관찰의 대상
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
