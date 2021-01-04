#pragma once

#include <Windows.h>

namespace DLL {
	void init();
	void quit();
	DWORD WINAPI main(LPVOID lp);
}
