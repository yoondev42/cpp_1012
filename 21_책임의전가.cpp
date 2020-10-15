// 21_책임의전가.cpp

// Chain of Responsibility Pattern
#include <iostream>
#include <map>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

class Window {
	int handle;
	static std::map<int, Window*> this_map;
public:
	void Create() {
		handle = IoMakeWindow(foo);
		this_map[handle] = this;
	}

	virtual void OnLButtonDown() {}
	virtual void OnKeyDown() {}

	static int foo(int handle, int msg, int param1, int param2) {
		Window* self = this_map[handle];
		switch (msg) {
		case WM_LBUTTONDOWN:
			self->OnLButtonDown();
			break;
		case WM_KEYDOWN:
			self->OnKeyDown();
			break;
		}

		return 0;
	}
};

std::map<int, Window*> Window::this_map;

//---------------------------
class MyWindow : public Window {
public:
	void OnLButtonDown() override {
		cout << "MyWindow LButton" << endl;
	}
};

int main() {
	MyWindow w;
	w.Create();      // 이 순간 윈도우가 만들어집니다.
					 // 왼쪽 마우스 버튼을 누르면, 출력이 되어야 합니다.

	IoProcessMessage();
}