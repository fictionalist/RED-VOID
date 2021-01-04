#include "Memory.hpp"

#include <Windows.h>

/* Memory namespace:
	* provides a helper macro to obtain the value of a given part of the memory.
*/

unsigned long Memory::baseAddress = 0x0;

bool Memory::init() {
	baseAddress = (unsigned long)GetModuleHandle(NULL);
	return true;
}
