// 메세지맵.cpp
#include <iostream>
#include <map>
using namespace std;

#include "ioacademy.h"
using namespace ioacademy;


// Window: 제공하는 메세지의 종류가 1000가지가 넘습니다.
// 즉 아래처럼 구현하면, 가상 함수 테이블의 크기가 엄청 커지는 문제가 있습니다.
//  : MFC
//    가상 함수를 이용해서 메세지를 처리할 때, 가상 함수 크기로 인해 
//    발생하는 오버헤드를 줄이기 위한 기술을 사용하고 있습니다.
//    => 메세지맵

class Window;                     // 전방 선언
struct AFX_MSG {
	int message;                  // 메세지 번호
	void (Window::* handler)();   // 처리할 함수의 주소
};


class Window {
	int handle;
	static std::map<int, Window*> this_map;
public:
	virtual ~Window() {}

	// 모든 자식 윈도우는 아래 함수를 재정의해서, 자신이 처리할 메세지와 핸들러의 배열을 
	// 반환해야 합니다.
	virtual AFX_MSG* GetMessageMap() { return 0; }

	void Create() {
		handle = IoMakeWindow(foo);
		this_map[handle] = this;
	}

	static int foo(int handle, int msg, int param1, int param2) {
		Window* self = this_map[handle];
		if (self == 0)
			return 0;

		// 1. 배열을 얻어온다.
		AFX_MSG* msgArray = self->GetMessageMap();
		// 처리할 메세지가 없는 경우
		if (msgArray == 0)
			return 0;

		// 약속: 배열의 마지막은 NULL로 끝난다.
		for (; msgArray->message != 0; ++msgArray) {
			if (msgArray->message == msg) {
				void (Window:: * f)() = msgArray->handler;
				(self->*f)();
			}
		}

		return 0;
	}
};

std::map<int, Window*> Window::this_map;

//---------------------------
class MyWindow : public Window {
public:
	void OnLButtonDown() { cout << "LBUTTON" << endl; }

	virtual AFX_MSG* GetMessageMap() {
		using HANDLER = void(Window::*)();

		static AFX_MSG msgMap[] = {
			{ WM_LBUTTONDOWN, static_cast<HANDLER>(&MyWindow::OnLButtonDown) },
			{ 0, 0 },
		};

		return msgMap;
	}
};

int main() {
	MyWindow w;
	w.Create();      // 이 순간 윈도우가 만들어집니다.
					 // 왼쪽 마우스 버튼을 누르면, 출력이 되어야 합니다.

	IoProcessMessage();
}