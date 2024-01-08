#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>    // std::tolower
#include <algorithm> // std::equal
#include <ctime>
#include "word_list.hpp" // All server handles

class WordHanlder
{
public:
	static std::vector<Word> wordsGlobal;
	static std::vector<Word> hard;
	static std::vector<Word> medium;
	static std::vector<Word> easy;

	// can load word in file into easy vector<word> for mode easy in game
	bool loadFromFile(const std::string &filename, std::vector<Word> &word)
	{
		std::ifstream file(filename);

		if (!file.is_open())
		{
			std::cerr << "Error opening file: " << filename << std::endl;
			return false;
		}

		// Read data from each line in the file
		while (!file.eof())
		{
			Word w;
			// Assuming the file format is: name age height
			file >> w.word >> w.totalCount >> w.successCount;

			// Check for errors while reading
			if (file.fail())
			{
				break; // Break if reading fails, assuming end of file or bad format
			}
			// Add the person to the vector
			word.push_back(w);
		}

		// Close the file
		file.close();
		return true;
	}


};

struct Word
{
	char word[50];
	int totalCount;
	int successCount;
};

extern std::vector<Word> wordsGlobal;
extern std::vector<Word> hard;
extern std::vector<Word> medium;
extern std::vector<Word> easy;

// get random from a vector Collection word
Word getRandomWord(std::vector<Word> &words);

// get random stirng from vector and remove it from this vector
Word getRandomAndRemove(std::vector<Word> &words);

int getLevel(char *word);

int getPoint(char *word);

bool loadFromFile(const std::string &filename, std::vector<Word> &word);

void writeWordsToFile(const std::string &filename, const std::vector<Word> &words);

std::vector<Word>::iterator findWord(std::vector<Word> &words, char *word);

int getLevel(std::vector<Word> &words, char *word);

int getPoint(std::vector<Word> &words, char *word);

void updateWord(std::vector<Word> &words, char *word, bool correct);

#endif