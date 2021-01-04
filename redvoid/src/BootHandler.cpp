#include "BootHandler.hpp"

/* BootHandler namespace:
	* used to force the game to enter Versus mode.
	* will likely be removed/replaced for a proper control flow for the project.
*/

#include <Definitions.hpp>
#include <Windows.h>

bool BootHandler::init() {
	unsigned long baseAddress = (unsigned long)GetModuleHandle(NULL); 
#define VALUE_OF(x) * (unsigned long*)(baseAddress + x)
	VALUE_OF(UNICLR_P1_SIDE_PLAYER) = 0;
	VALUE_OF(UNICLR_P2_SIDE_PLAYER) = 1;
	VALUE_OF(UNICLR_CURRENT_SCENE) = (unsigned long)GameScenes::CharacterSelect;

	void (*startVersus)() = (void(*)())(baseAddress + UNICLR_START_VERSUS);

	startVersus();

	return true;
}