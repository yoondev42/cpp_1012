// 34_메멘토.cpp
//  Memento Pattern
//  의도: 객체의 상태를 내부적으로 저장해두었다가,
//       언제라도 그 상태로 복구 가능하게 하는 패턴
//       => Snapshot 저장 / 복원

#include <iostream>
#include <vector>
using namespace std;

class User {
  int level_;
  int exp_;
  int x_;
  int y_;

  // 객체의 상태를 저장하기 위해 꼭 필요한 항목을 캡슐화한다.
  struct Memento {
    int level_;
    int exp_;
    int x_;
    int y_;

    Memento(int level, int exp, int x, int y) : level_(level), exp_(exp), x_(x), y_(y) {}
  };

  vector<Memento*> snapshots;
public:
  User(): level_(1), exp_(0), x_(0), y_(0) {
  }

  void Print() {
    printf("User(level=%d, exp=%d, x=%d, y=%d)\n", level_, exp_, x_, y_);
  }

  void Do() {
    level_++;
    exp_ += 100;
    x_ += 10;
    y_ += 20;
  }

  int Save() {
    Memento* m = new Memento(level_, exp_, x_, y_);
    snapshots.push_back(m);

    // 핵심: token을 반환해야 한다. - index
    return snapshots.size() - 1;
  }

  void Load(int token) {
    Memento* m = snapshots[token];

    level_ = m->level_;
    exp_ = m->exp_;
    x_ = m->x_;
    y_ = m->y_;
  }
};

int main() {
  User user;
  user.Do();
  user.Do();
  user.Do();

  // Save
  int token = user.Save();
  user.Print();

  user.Do();
  user.Do();
  int token2 = user.Save();
  printf("복원 전\n"); 
  user.Print();
  printf("복원 후\n");
  user.Load(token);
  user.Print();

  printf("복원 후2\n");
  user.Load(token2);
  user.Print();
}




// 문제점
// 1. 사용자 상태의 정보가 변경될 때마다, Save / Load도 변경되어야 한다.
// 2. User의 상태를 저장하거나 복원하기 위해서는 내부 상태가 외부로 공개되어야 한다.
#if 0
class User {
  int level_;
  int exp_;
  int x_;
  int y_;
public:
  void Save(int* level, int* exp, int* x, int* y) {
    *level = level_;
    *exp = exp_;
    *x = x_;
    *y = y_;
  }

  void Load(int level, int exp, int x, int y) {
    level_ = level;
    exp_ = exp;
    x_ = x;
    y_ = y;
  }
};
#endif