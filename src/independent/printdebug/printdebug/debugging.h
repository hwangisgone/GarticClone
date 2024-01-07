#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <string>
std::string test_me(std::string x);
void load_test_file(const std::string& filePath);


#ifdef NDEBUG
	#define TEST_PRINT(x)
	#define DEBUG_PRINT(x) 
	#define DEBUG_COUT(x)
	#pragma message("DEBUG DISABLED FOR RELEASE")
#else
	// #pragma message "NOT WORKING!!!!"
	#ifdef TEST_ENABLED
		#define TEST_CHECK(x) test_me(x)
	#else
		#define TEST_CHECK(x) x
	#endif

	#include <iostream>
	#define TEST_PRINT(x) do { std::cerr << "\033[96mTEST: \033[0m" << TEST_CHECK(x) << std::endl; } while (0)
	#define DEBUG_PRINT(x) do { std::cerr << "DEBUG: " << x << std::endl; } while (0)
	#define DEBUG_COUT(x) do { std::cerr << x; } while (0)
#endif



#endif