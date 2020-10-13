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
  
  std::string getName() const {
    return name;
  }
};

class File : public Item {
  int size;
public:
  File(const string& s, int sz) : Item(s), size(sz) {}
  ~File() {
    cout << "파일 삭제: " << getName() << endl;
  }

  int getSize() override {
    return size;
  }
};

class Folder : public Item {
  vector<Item*> v;
public:
  Folder(const string& s) : Item(s) {}
  ~Folder() {
    for (Item* e : v) {
      delete e;
    }
    cout << "폴더 삭제: " << getName() << endl;
  }

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

  delete fol1;
  // 복합객체는 자신이 포함하고 있는 객체를 파괴하는 책임도 가지고 있습니다.
  //  약속: 복합 객체에 등록하는 모든 객체는 new를 통해 생성되어야 한다.
}