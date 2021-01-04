#include "Patch.hpp"

/* PatchList namespace:
	* provides an interface to apply or restore game patches through the Patch struct.
	* the Patch struct holds vectors of bytes to apply and restore patches directly on game memory.
*/

#include <Definitions.hpp>

#include <stdarg.h>
#include <Windows.h>

#include "Memory.hpp"

// NetworkDetour patch: prevents the game from entering the Network mode (which will likely cause a lot of problems), and detours into 2 player Versus mode.
static Patch NetworkDetour = { UNICLR_MAINMENU_DECISION_NETWORK_DETOUR, { 0xEB, 0xD0, 0x90, 0x90, 0x90, 0x90 } };

void Patch::apply() {
	if (active) return;
	void* addr = (void*)GAME_ADDRESS(address);

	if (backup.size() == 0) {
		backup.resize(bytes.size());
	}

	DWORD oldProtect, newProtect = PAGE_EXECUTE_READWRITE;
	VirtualProtect(addr, bytes.size(), newProtect, &oldProtect);
	memcpy(backup.data(), addr, bytes.size());
	memcpy(addr, bytes.data(), bytes.size());
	VirtualProtect(addr, bytes.size(), oldProtect, &newProtect);

	active = true;
}

void Patch::restore() {
	if (!active) return;
	void* addr = (void*)GAME_ADDRESS(address);

	DWORD oldProtect, newProtect = PAGE_EXECUTE_READWRITE;
	VirtualProtect(addr, bytes.size(), newProtect, &oldProtect);
	memcpy(backup.data(), addr, bytes.size());
	memcpy(addr, bytes.data(), bytes.size());
	VirtualProtect(addr, bytes.size(), oldProtect, &newProtect);

	active = false;
}

bool PatchList::init() {
	NetworkDetour.apply();
	return true;
}

bool PatchList::revert() {
	NetworkDetour.restore();
	return true;
}