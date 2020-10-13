// 단일 객체 - File
// 복합 객체 - Folder
//     단일 인터페이스 - getSize()
//     공통의 부모    - Item

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