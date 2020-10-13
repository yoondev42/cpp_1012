// 라이브러리: 프로그램 개발에 필요한 도구의 집합
//           함수 / 클래스 집합
// 프레임워크: 도구 집합 + 미리 정의된 실행 흐름
//           => 템플릿 메소드 패턴이 적용되는 케이스가 많다.
//              전체적인 흐름을 프레임워크 안에 두고, 각 단계를 가상함수화해서
//              오버라이드를 통해 재정의하도록 구현되었다.
//           Android, iOS, MFC ...

// main 함수를 라이브러리 안에서 관리해보자.
// ex) MFC를 이용해서 만들어진 예제


// 프레임워크 내부 코드
//-------------------

class CWinApp;
CWinApp* g_app;

// Application 상태를 관리하는 객체
class CWinApp {
public:
	// 2. CWinApp()의 생성자에서 g_app에 객체의 주소를 저장합니다.
	CWinApp() { g_app = this; }
	virtual bool InitInstance() { return false; }
	virtual int ExitInstance() { return 0; }
	virtual int Run() { return 0; }
};

CWinApp* AfxGetApp() { return g_app; }

// 3. main함수 수행
int main() {
	CWinApp* pApp = AfxGetApp();

	if (pApp->InitInstance())
		pApp->Run();
	pApp->ExitInstance();
}
//-----------------------------------
#include <iostream>
using namespace std;

// 아래가 위 프레임워크의 사용자 코드 입니다.
// 1. CWinApp의 파생 클래스를 만들어야 합니다.
// 2. InitInstance()의 가상함수를 재정의해서, 
//    프로그램 초기화시 해야 하는 동작을 정의합니다.
// 3. 사용자가 만들 클래스를 전역적으로 한개를 생성해야 합니다.
class CMyApp : public CWinApp {
public:
	bool InitInstance() override {
		cout << "프로그램 시작" << endl;
		return true;
	}

	int ExitInstance() override {
		cout << "프로그램 종료" << endl;
		return 0;
	}
};

CMyApp theApp;
// 1. 전역 객체의 생성은 main 함수가 호출되기 전에 수행된다.