// 21_책임의전가.cpp

// Chain of Responsibility Pattern
//  의도: 발생한 이벤트를 다음 객체에게 전달하는 패턴

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

	virtual bool OnLButtonDown() { return false; }
	virtual void OnKeyDown() {}

	static int foo(int handle, int msg, int param1, int param2) {
		Window* self = this_map[handle];
		switch (msg) {
		case WM_LBUTTONDOWN:
			self->FireLButtonDown();
			break;
		case WM_KEYDOWN:
			self->OnKeyDown();
			break;
		}

		return 0;
	}

	// 아래 코드가 책임의 전가(Chain of Responsibility) 패턴의 핵심 코드 입니다.
	void FireLButtonDown() {
		// 1. 먼저 자신이 처리를 시도합니다.
		//  true: 다음 객체에게 전달하지 않는다.
		// false: 처리가 완료되지 않았음으로, 다음객체에게 전달한다.
		if (OnLButtonDown())
			return;

		// 2. 처리되지 않은 경우, 부모에게 전달한다.
		if (parent) {
			parent->FireLButtonDown();
		}
	}

};

std::map<int, Window*> Window::this_map;

//---------------------------
class MyWindow : public Window {
public:
	bool OnLButtonDown() override {
		cout << "MyWindow LButton" << endl;
		return false;
	}
};

class ImageView : public Window {
public:
	bool OnLButtonDown() override {
		cout << "ImageView LButton" << endl;
		return false;
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