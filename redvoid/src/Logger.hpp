#pragma once

#include <string>

namespace Logger {
	bool init();
	void log(std::string pattern, ...);
}