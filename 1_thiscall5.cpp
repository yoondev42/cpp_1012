#include <iostream>
#include <map>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

// map을 이용해서, this를 저장하고 불러오는 방법.

class Clock {
	std::string name;

	static std::map<int, Clock*> this_map;

public:
	Clock(const std::string& s) : name(s) {}

	void Start(int ms) {
		int id = IoSetTimer(ms, timerHandler);
		this_map[id] = this;
	}

	static void timerHandler(int id) {
		Clock* self = this_map[id];
		cout << self->name << endl;
		
		// cout << name << endl;
	}
};

map<int, Clock*> Clock::this_map;



int main() {
	Clock c1("AAA");
	Clock c2("\tBBB");

	c1.Start(1000); // 1초에 한번씩 이름을 출력해야 합니다.
	c2.Start(500);  

	IoProcessMessage();
}



#if 0
void foo(int id) {
	cout << "foo: " << id << endl;
}

int main() {
	int n1 = IoSetTimer(1000, foo);
	int n2 = IoSetTimer(500, foo);

	IoProcessMessage();
}
#endif