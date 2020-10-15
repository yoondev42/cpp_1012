// 21_책임의전가.cpp

// Chain of Responsibility Pattern
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;

class Window {
	int handle;
	static std::map<int, Window*> this_map;

	//--------------------
	Window* parent;              // 부모 윈도우
	vector<Window*> children;    // 자식 윈도우는 여러개 입니다.
public:
	Window() : parent(nullptr) {}

	void AddChild(Window* p) {
		p->parent = this;
		children.push_back(p);

		// C 함수를 통해 자식 윈도우를 붙인다.
		IoAddChild(handle, p->handle);
	}
	//---------------------

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

class ImageView : public Window {
public:
	void OnLButtonDown() override {
		cout << "ImageView LButton" << endl;
	}
};

int main() {
	MyWindow w;
	w.Create();      

	ImageView w2;
	w2.Create();

	w.AddChild(&w2);
					 
	IoProcessMessage();
}