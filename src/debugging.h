#ifndef DEBUGGING_H
#define DEBUGGING_H

#ifdef NDEBUG
	#define DEBUG_PRINT(x) 
#else
	#include <iostream>
	#define DEBUG_PRINT(x) do { std::cerr << "DEBUG: " << x << std::endl; } while (0)
#endif

#endif