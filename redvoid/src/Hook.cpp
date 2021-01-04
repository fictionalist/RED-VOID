#include "Hook.hpp"

/* Hook namespace:
	* will provide a framework for implementing hooks and detour game functions, for purposes like intercepting the game loop to then force the game to 'rewind' and simulate the frames rolled back.

	* character select
	* match start
	* round start
	* round end
	* match end
	* on frame
*/

#include <Definitions.hpp>

Hook::Hook(unsigned long _address) {
	address = _address;
}

bool HookList::init() {
	return true;
}