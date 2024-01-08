#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>    // std::tolower
#include <algorithm> // std::equal
#include <random>		// std::shuffle
#include <ctime>
#include "word_list.hpp" // All server handles

struct Word
{
	char word[50];
	int totalCount;
	int successCount;
	int level;
	//	0 easy
	//	1 medium
	//	2 hard
};

class WordHanlder {
private:
	// static std::vector<Word> wordsGlobal;
	// Globals

	// std::vector<Word> wordCollection;
	void setMode(int modeGame);
	int modeGame;
public:
	// can load word in file into easy vector<word> for mode easy in game
	static bool loadFromFile(const std::string &filename, std::vector<Word> &word);
	static void writeWordsToFile(const std::string& filename, const std::vector<Word>& words);

	static int getLevel(char *word);
	static int getPoint(char *word);
	static void updateWord(char *word, bool correct);

	static std::vector<Word> wordsGlobal;
	std::vector<Word> wordCollection;
	
	// get random from a vector Collection word
	Word getRandomWord(std::vector<Word>& words);

	// get random stirng from vector and remove it from this vector
	Word getRandomAndRemove(std::vector<Word>& words);

	static std::vector<Word>::iterator findWord(char *word);
};



#endif