#pragma once

#include <string>

namespace Configuration {
	bool init();
	bool load();
	bool save();
	template <typename T> T get(std::string key);
	template <typename T> void set(std::string key, T value);
}