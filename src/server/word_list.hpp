#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <unordered_map>
#include <string>
#include <vector>
#include "word_list.hpp" // All server handles

std::string getRandomString(const std::vector<std::string>& vec);

std::string getStringCollection(const std::vector<std::string>& vec);

std::vector<std::string> hard;

std::vector<std::string> medium;

std::vector<std::string> easy;

#endif