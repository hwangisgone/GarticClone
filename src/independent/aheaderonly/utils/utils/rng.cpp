#include "rng.hpp"

std::random_device rd;		// Global random_device
std::mt19937 gameRng(rd());	// Global Mersenne Twister engine seeded with the global random_device
