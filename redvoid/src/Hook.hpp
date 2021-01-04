#pragma once

class Hook {
private:
	unsigned long address;
public:
	Hook(unsigned long address);
};

namespace HookList {
	bool init();
}