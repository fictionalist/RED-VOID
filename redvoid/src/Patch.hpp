#pragma once

#include <vector>

typedef unsigned char byte;

struct Patch {
	unsigned long address;
	const std::vector<byte> bytes;
	mutable std::vector<byte> backup;

	void apply();
	void restore();
	bool active = false;
};

namespace PatchList {
	bool init();
	bool revert();
}