// CalcProxy.cpp
#include "ioacademy.h"
using namespace ioacademy;

#include "ICalc.h"

class Calc : public ICalc {
	int handle;
public:
	Calc() {
		handle = IoFindServer("CalcServer");
	}

	int Add(int a, int b) {
		return IoSendServer(handle, 1, a, b);
	}

	int Sub(int a, int b) {
		return IoSendServer(handle, 2, a, b);
	}
};

// DLL 안쪽에 Proxy를 만드는 함수를 같이 제공해야 합니다.
extern "C"
__declspec(dllexport)
ICalc* CreateCalc() {
	return new Calc();
}

// 빌드하는 방법
// cl CalcProxy.cpp /LD /link user32.lib gdi32.lib kernel32.lib