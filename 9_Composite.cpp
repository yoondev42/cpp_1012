// 단일 객체 - File
// 복합 객체 - Folder
//     단일 인터페이스 - getSize()
//     공통의 부모    - Item
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item {
  string name;
public:
  Item(const string& s) : name(s) {}
  virtual ~Item() {}

  virtual int getSize() = 0;
};

class File : public Item {
  int size;
public:
  File(const string& s, int sz) : Item(s), size(sz) {}

  int getSize() override {
    return size;
  }
};

class Folder : public Item {
  vector<Item*> v;
public:
  Folder(const string& s) : Item(s) {}

  void addItem(Item* p) { v.push_back(p); }

  int getSize() {
    int sum = 0;
    for (Item* e : v) {
      sum += e->getSize();
    }
    return sum;
  }
};



int main()
{
	Folder* fol1 = new Folder("ROOT");
	Folder* fol2 = new Folder("A");

	File* f1 = new File("a.txt", 10); // 이름, 크기
	File* f2 = new File("b.txt", 20);

	fol2->addItem( f1);
	fol1->addItem( f2);
	fol1->addItem(fol2);
	cout << f2->getSize() << endl; 
	cout << fol2->getSize() << endl;
	cout << fol1->getSize() << endl;
}