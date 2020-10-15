// 21_책임의전가.cpp

// Chain of Responsibility Pattern
//  의도: 발생한 이벤트를 처리되지 않을 경우, 다음 객체에게 전달하는 패턴
//        처리할 수 있을 때까지 고리에 따라 이벤트를 전달한다.

//  GUI 라이브러리 - 터치(클릭) 이벤트
//  메뉴(MFC)
//       View -> Document -> Frame -> App 순서로 메뉴 메시지가 전달된다.

//  결과: 이벤트와 이벤트 처리 객체의 결합도를 줄일 수 있다.
//   객체 지향 5대 원칙 - SOLID
//     SRP: 단일 책임의 원칙 - 모듈은 단 하나의 책임을 가져야 한다.


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
		return true;
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