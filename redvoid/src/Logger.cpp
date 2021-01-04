#include "Logger.hpp"

/* Logger namespace:
	* provides logging tools for debugging the project once the DLL is injected.
	* spawns a console for the game for real-time debugging (mostly printing stuff).
*/

#include <Windows.h>

#include <string>
#include <sstream>
#include <stdarg.h>
#include <fstream>

HANDLE consoleOutput = INVALID_HANDLE_VALUE;
std::ofstream file;

bool Logger::init() {
	if (!AllocConsole()) {
		return false;
	}
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (consoleOutput == INVALID_HANDLE_VALUE) {
		return false;
	}

	file = std::ofstream("rollback_log.txt");

	log("Logger initialized.");
	return true;
}

void Logger::log(std::string pattern, ...) {
	if (!file.is_open()) {
		file.open("rollback_log.txt");
	}
	SYSTEMTIME time = {};
	GetLocalTime(&time);
	
	const char* initString = "[%04d/%02d/%02d %02d:%02d:%02d] %s\n";
	char mbuf[512];
	memset(mbuf, 0, 512);
	sprintf_s(mbuf, 512, initString, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, pattern.c_str());

	char buf[512];
	memset(buf, 0, 512);

	va_list va;
	va_start(va, pattern);
	vsprintf_s(buf, 512, mbuf, va);
	va_end(va);

	WriteFile(consoleOutput, buf, strlen(buf), nullptr, 0);

	file << buf;
	file.close();
}