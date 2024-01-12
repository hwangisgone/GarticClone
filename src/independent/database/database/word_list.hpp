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
#include <cstring>

struct Word
{
	char word[50];
	int totalCount;
	int successCount;
	int level;
	//	0 easy
	//	1 medium
	//	2 hard

	int getWordPoint() const {
		if (level == 0) return 30;
		else if (level == 1) return 50;
		else if (level == 2) return 80;
		else return -999;	// Breaks everything
	}

	bool isTheSame(const char *str) const {
		return strncmp(str, word, 50) == 0;
	}
};

class WordHandler {
private:

	// Globals

	std::vector<Word> wordCollection;
	void setDiff(int difficulty);
	int difficulty;
public:
	static std::vector<Word> wordsGlobal;
	// can load word in file into easy vector<word> for easy in game
	static bool loadFromFile(const std::string &filename, std::vector<Word> &word);
	static void writeWordsToFile(const std::string& filename, const std::vector<Word>& words);

	static int getLevel(char *word);
	static void updateWord(char *word, bool correct);
	
	// get random from a vector Collection word
	Word getRandomWord();

	// get random stirng from vector and remove it from this vector
	Word getRandomAndRemove();

	static std::vector<Word>::iterator findWord(char *word);
};



#endif