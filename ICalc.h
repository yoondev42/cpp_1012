
#ifndef ICALC_H
#define ICALC_H

#include "ioacademy.h"
using namespace std;

struct ICalc {
	virtual ~ICalc() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;

	static ICalc* CreateInstance() {
		void* addr = IoLoadModule("CalcProxy.dll");
		using FP = ICalc * (*)();

		FP f = static_cast<FP>(IoGetFunctionAddress(addr, "CreateCalc"));

		ICalc* pCalc = f();
		return pCalc;
	}
};


#endif

