#include "DLL.hpp"

/* DLL namespace:
	* acts as an entry point to the DLL by spawning a separate thread for our own purposes; important so certain techniques do not produce deadlocks (crash the game but in a spectacularly awful way), and allows us to modify game memory directly.
	* focused on initializing and cleaning up components.
*/

#include "Logger.hpp"
#include "Configuration.hpp"
#include "Memory.hpp"
#include "Patch.hpp"
#include "WindowProc.hpp"
#include "BootHandler.hpp"
#include "GameState.hpp"

#include <Windows.h>

bool initialized = false;

DWORD WINAPI DLL::main(LPVOID lp) {
	UNREFERENCED_PARAMETER(lp);
	if (!Logger::init()) {
		MessageBeep(MB_ICONERROR);
		return FALSE;
	}

	if (!Memory::init()) {
		Logger::log("Failed to start the Memory component.");
		return FALSE;
	}

	if (!Configuration::init()) {
		Logger::log("Failed to start the Configuration component.");
		return FALSE;
	}

	if (!PatchList::init()) {
		Logger::log("Failed to start the PatchList component.");
		return FALSE;
	}

	if (!WindowProc::init()) {
		Logger::log("Failed to start the WindowProc component.");
		return FALSE;
	}

	if (!GameState::init()) {
		Logger::log("Failed to start the GameState component.");
		return FALSE;
	}
	return TRUE;
}

void DLL::init() {
	if (initialized == true) return;
	initialized = true;
	CreateThread(NULL, NULL, DLL::main, NULL, NULL, NULL);
}

void DLL::quit() {
	if (initialized == true) {
		PatchList::revert();
	}
}