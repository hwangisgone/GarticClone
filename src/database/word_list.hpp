#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <unordered_map>
#include <string>
#include <vector>
#include "word_list.hpp" // All server handles

struct Word{
    char word[50];
	int totalCount;
	int successCount;
};

std::vector<Word> wordsGlobal;
// get random from a vector Collection word 
Word getRandomWord(std::vector<Word>& words);

// get random stirng from vector and remove it from this vector
Word getRandomAndRemove(std::vector<Word>& words);

std::vector<Word> hard;

std::vector<Word> medium;

std::vector<Word> easy;

int getLevel(char *word);

int getPoint(char *word);

bool loadFromFile(const std::string& filename, std::vector<Word>& word);

void writeWordsToFile(const std::string& filename, const std::vector<Word>& words);

std::vector<Word>::iterator findWord(std::vector<Word> &words, char *word);

int getLevel(std::vector<Word>& words, char *word);

int getPoint(std::vector<Word>& words, char *word);

void updateWord(std::vector<Word>& words, char *word, bool correct); 

#endif