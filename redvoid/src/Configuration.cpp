#include "Configuration.hpp"

#include <string>
#include <fstream>
#include <vector>

std::fstream configFile;

struct configItem {
};

static std::vector<configItem> configList;

void buildDefaults() {

}

bool Configuration::init() {
	configFile = std::fstream("./rollback.cfg");

	return true;
}

bool Configuration::save() {
	if (!configFile.is_open()) {
		configFile.open("./rollback.cfg");
	}
	return true;
}