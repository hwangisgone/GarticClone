#include "debugging.h"

#ifdef TEST_ENABLED
	#pragma message "Test ENABLED!!!"
#endif

#ifdef NDEBUG
	// #pragma message "NOT WORKING!!!!"
#endif

#include <fstream>
#include <queue>

std::queue<std::string> lines;

std::string test_me(std::string x) {
	if (lines.empty()) {
		std::cerr << "empty test!" << std::endl;
		return x;
	}

	if (x == lines.front()) {
		lines.pop();
		return "\033[32m" + x + "\033[0m";
	} else {
		lines.pop();
		return "\033[31m" + x + "\033[0m";
	}

	return x;
}


void load_test_file(const std::string& filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push(line);
    }

    inputFile.close();
}