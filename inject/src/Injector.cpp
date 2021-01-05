#include "Injector.hpp"
#undef UNICODE

#include <Definitions.hpp>

#include <stdio.h>
#include <string>

#include <Windows.h>
#include <DbgHelp.h>
#include <TlHelp32.h>
#include <Definitions.hpp>

char* formatSystemMessage(DWORD err) {
	char* buf = nullptr;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, 0, buf, 0, 0);
	return buf;
}

bool getDebugPrivilege() {
	TOKEN_PRIVILEGES tp = { 0 };
	HANDLE token = NULL;
	bool success = false;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
			success = AdjustTokenPrivileges(token, FALSE, &tp, 0, NULL, NULL);
		}
		CloseHandle(token);
	}
	return success;
}

bool loadSymbol(const char* name, HANDLE proc) {
	MODULEENTRY32 modEntry = { 0 };
	HANDLE handle;
	DWORD64 returnAddress = 0;
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetProcessId(proc));
	if (handle != INVALID_HANDLE_VALUE) {
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(handle, &modEntry)) {
			do {
				if (_stricmp(modEntry.szModule, name) == 0) {
					returnAddress = SymLoadModuleEx(proc, NULL, modEntry.szExePath, modEntry.szModule, (DWORD64)modEntry.modBaseAddr, modEntry.modBaseSize, NULL, 0);
					break;
				}
			} while (Module32Next(handle, &modEntry));
		}
		CloseHandle(handle);
	}
	return (returnAddress != 0);
}

void getGameProcess(HANDLE* gameProcess) {
	HWND gameWindow = NULL;
	bool found = false;
	printf("Waiting for UNDER NIGHT IN-BIRTH Exe:Late[cl-r] to be launched.\n");
	while (true) {
		Sleep(50);
		gameWindow = FindWindow(NULL, "UNDER NIGHT IN-BIRTH Exe:Late[cl-r]");
		if (gameWindow != NULL) break;
	}

	DWORD processID = 0;
	GetWindowThreadProcessId(gameWindow, &processID);
	if (processID == 0) {
		printf("Failed to get process ID. Error 0x%X: \n%s", GetLastError(), formatSystemMessage(GetLastError()));
		return;
	}

	*gameProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
}

bool Injector::init() {
	printf("Attempting to inject DLL.\n");
	if (!getDebugPrivilege()) {
		printf("Failed to get debug privilege. Error 0x%X: \n%s\n", GetLastError(), formatSystemMessage(GetLastError()));
		return false;
	}

	HANDLE gameProcess = 0;
	getGameProcess(&gameProcess);
	if (gameProcess == 0) {
		return false;
	}

	if (!SymInitialize(gameProcess, NULL, FALSE)) {
		printf("Failed to initialized symbols. Error 0x%X: \n%s\n", GetLastError(), formatSystemMessage(GetLastError()));
		return false;
	}
	if (!loadSymbol("kernel32.dll", gameProcess)) {
		printf("Failed to load symbols for kernel32.dll. Error 0x%X: \n%s\n", GetLastError(), formatSystemMessage(GetLastError()));
		return false;
	}

	SYMBOL_INFO symbol = { 0 };
	symbol.SizeOfStruct = sizeof(symbol);
	if (!SymFromName(gameProcess, "LoadLibraryA", &symbol) || symbol.Address == 0) {
		printf("Failed to locate LoadLibraryA. Error 0x%X: \n%s\n", GetLastError(), formatSystemMessage(GetLastError()));
		return false;
	}

	LPTHREAD_START_ROUTINE loadLibraryAddr = reinterpret_cast<LPTHREAD_START_ROUTINE>(symbol.Address);

#ifdef DEBUG
	printf("LoadLibraryA address: 0x%08X\n", loadLibraryAddr);
#endif

	void* dllNameAddress = VirtualAllocEx(gameProcess, NULL, sizeof(DLLName), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (dllNameAddress == nullptr) {
		printf("Failed to allocate memory on the game. Error 0x%X: \n%s\n", GetLastError(), formatSystemMessage(GetLastError()));
		return false;
	}

	if (!WriteProcessMemory(gameProcess, dllNameAddress, DLLName, sizeof(DLLName), NULL)) {
		printf("Failed to write DLL address. Error 0x%X: \n%s\n", GetLastError(), formatSystemMessage(GetLastError()));
		return false;
	}

	HANDLE loadThread = CreateRemoteThread(gameProcess, NULL, NULL, loadLibraryAddr, dllNameAddress, NULL, NULL);

	DWORD result = WaitForSingleObject(loadThread, 1000);
	if (result != WAIT_OBJECT_0) {
		printf("Failed to inject DLL.\n");
		CloseHandle(gameProcess);
		VirtualFreeEx(gameProcess, dllNameAddress, 0, MEM_RELEASE);
		system("@echo off");
		system("pause");
		system("@echo on");
		return false;
	}

	printf("Injected DLL.");

	CloseHandle(gameProcess);
	VirtualFreeEx(gameProcess, dllNameAddress, 0, MEM_RELEASE);

	return true;
}