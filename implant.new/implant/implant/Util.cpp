#include "Util.h"

std::vector <std::string> util::split(std::string cmd, char delimiter) {
		std::string line;
		std::vector <std::string> vec;
		std::stringstream ss(cmd);

		while (std::getline(ss, line, delimiter)) {
			vec.push_back(line);
		}
		return vec;
}
