#pragma once

namespace Memory {
	extern unsigned long baseAddress;

	bool init();
}

#define VALUE_OF(addr) *(unsigned long*)(Memory::baseAddress + addr)
#define GAME_ADDRESS(addr) (Memory::baseAddress + addr)