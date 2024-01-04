#ifndef DEBUGGING_H
#define DEBUGGING_H

#ifdef NDEBUG
	#define DEBUG_PRINT(x) 
	#define DEBUG_COUT(x)
	#pragma message("DEBUG DISABLED FOR RELEASE")
#else
	// #pragma message "NOT WORKING!!!!"
	#include <iostream>
	#define DEBUG_PRINT(x) do { std::cerr << "DEBUG: " << x << std::endl; } while (0)
	#define DEBUG_COUT(x) do { std::cerr << x; } while (0)
#endif

#endif