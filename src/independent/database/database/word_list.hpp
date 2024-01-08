#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>   	// std::tolower
#include <algorithm>	// std::equal
#include <random>		// std::shuffle
#include <ctime>

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

class WordHandler {
private:
	static std::vector<Word> wordsGlobal;
	// Globals

	std::vector<Word> wordCollection;
	void setMode(int modeGame);
	int modeGame;
public:
	// can load word in file into easy vector<word> for mode easy in game
	static bool loadFromFile(const std::string &filename, std::vector<Word> &word);
	static void writeWordsToFile(const std::string& filename, const std::vector<Word>& words);

	static int getLevel(char *word);
	static int getPoint(char *word);
	static void updateWord(char *word, bool correct);
	
	// get random from a vector Collection word
	Word getRandomWord();

	// get random stirng from vector and remove it from this vector
	Word getRandomAndRemove();

	static std::vector<Word>::iterator findWord(char *word);
};



#endif