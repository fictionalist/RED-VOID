#include <Definitions.hpp>
#include <Windows.h>
#include <stdio.h>

#include "Injector.hpp"



int main() {
	system("start steam://rungameid/801630");

	while (!FindWindowA(WINDOW_NAME, NULL)) {
		Sleep(100);
	}

	if (!Injector::init()) {
		return 1;
	}

	return 0;
}