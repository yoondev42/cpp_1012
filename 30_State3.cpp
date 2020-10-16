// State Pattern
#include <iostream>
using namespace std;

// 상태 패턴
class Hero {
  int gold;
  int itemState;
public:
  void Run()    { cout << "Hero Run" << endl;   }
  void Attack() { cout << "Hero Attack" << endl;}
};

int main() {
  Hero h;
  h.Attack();
}