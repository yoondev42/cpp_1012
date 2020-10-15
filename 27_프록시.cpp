
// Proxy Pattern
//  대리자 패턴: 기존의 역활을 대신하는 클래스
//       1. Smart Proxy
//       2. Remote Proxy
//----------------------------------

#if 1
// Process:    A(Client)                    B(Server)
//                                         add(int, int)
//                                         sub(int, int)

#endif


// 27_프록시.cpp
#include <iostream>
#include "ioacademy.h"
using namespace std;
using namespace ioacademy;

#include "ICalc.h"

// Calc 라는 클래스는 서비스의 개발자가 제공합니다.
//  => '인터페이스'를 약속해야 합니다.

int main() {
	ICalc* pCalc = ICalc::CreateInstance();

	cout << pCalc->Add(10, 20) << endl;
	cout << pCalc->Sub(20, 10) << endl;
}

#if 0
int main() {
	// CreateCalc 함수를 CalcProxy.dll에서 찾아서 호출해서, 프록시 객체를
	// 생성할 수 있습니다.
	void* addr = IoLoadModule("CalcProxy.dll");
	using FP = ICalc * (*)();

	FP f = static_cast<FP>(IoGetFunctionAddress(addr, "CreateCalc"));

	ICalc* pCalc = f();

	cout << pCalc->Add(10, 20) << endl;
	cout << pCalc->Sub(20, 10) << endl;
}
#endif









// IoFindServer / IoSendServer를 사용하지 않고, 마치
// 로컬에 클래스가 있는 것처럼 사용할 수 있도록 하고 싶다.

// 아래의 클래스는 서버 개발자가 제공합니다.
// 서비스 제공자가 서비스를 아래와 같은 클래스로 제공한다면,
// 서비스의 이용자는 IPC와 프로토콜에 대한 이해 없이, 해당 서비스 기능을
// 이용할 수 있습니다.
// => 아래와 같이 원격의 서비스를 대신하는 클래스 - 리모트 프록시


#if 0
class Calc {
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

int main() {
	Calc calc;

	while (1) {
		cout << calc.Add(10, 20) << endl;
		getchar();
		cout << calc.Sub(10, 20) << endl;
		getchar();
	}
}
#endif



#if 0
int main() {
	// 1. 서버 프로세스를 찾습니다.
	int handle = IoFindServer("CalcServer");
	cout << "서버 번호: " << handle << endl;

	while (1) {
		getchar();
		// 2. 서버로 메세지를 전송한다.
		cout << IoSendServer(handle, 1, 10, 20) << endl;
		getchar();
		cout << IoSendServer(handle, 2, 10, 20) << endl;
	}
}
#endif

