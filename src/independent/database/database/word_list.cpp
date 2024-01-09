#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>    // std::tolower
#include <algorithm> // std::equal
#include <ctime>

#include "word_list.hpp"
#include <utils/rng.hpp>

// Fixed everything
// https://www.reddit.com/r/Cplusplus/comments/xsd64h/static_variable_undefined_reference_error/
std::vector<Word> WordHandler::wordsGlobal;
// initialize empty vector c++
// "static" doesn't initialize it, it only declares

Word WordHandler::getRandomWord() {
	if (this->wordCollection.empty()) {
		return {"", 0, 0}; // Return an empty string if the vector is empty
	}

	// multithreading problem if use wordsGlobal
	std::shuffle(wordCollection.begin(), wordCollection.end(), gameRng);

	// Seed the random number generator with the current time
	std::srand(std::time(0));

	// Generate a random index within the range of the vector size
	std::size_t randomIndex = std::rand() % this->wordCollection.size();

	// Return the randomly selected string
	return this->wordCollection[randomIndex];
}


Word WordHandler::getRandomAndRemove() {
	if (this->wordCollection.empty()) {
		// Handle the case where the vector is empty
		return {"", 0, 0};
	}

	std::srand(std::time(0));

	// Generate a random index within the range of the vector size
	std::size_t randomIndex = std::rand() % this->wordCollection.size();

	// Get the randomly selected word
	Word randomWord = this->wordCollection[randomIndex];

	// Remove the word at the random index from the vector
	this->wordCollection.erase(this->wordCollection.begin() + randomIndex);

	return randomWord;
}

void WordHandler::setMode(int modeGame){
	Word randomWord ;
	if(modeGame == 0){
		// 6 word | 3 easy, 2 medium, 1 hard
		// 6 word - easy all
		for( int i = 1 ; i<= 6 ; i++)
		{
			Word w = this->getRandomWord();
			wordCollection.push_back(w);
		}
	}
	else if(modeGame == 1){ 
		// 8 word | 2 easy, 3 medium, 3 hard
		int a = 2;
		int b = 3;
		int c = 3;
		int sum = 0 ;
		while(sum < 8){
			Word w = this->getRandomWord();
			if(getLevel(w.word) == 1 && a > 0)
				{
					wordCollection.push_back(w);
					a--;
					sum++;
				}
			else if(getLevel(w.word) == 2 && b > 0){
					wordCollection.push_back(w);
					b--;
					sum++;
			}
			else{
				wordCollection.push_back(w);
				c--;
				sum++;
			}
		}
	} else if (modeGame == 2) {
		// 10 word | 2 easy, 3 medium, 5 hard
		int a = 2;
		int b = 3;
		int c = 5;
		int sum = 0 ;
		while(sum < 10){
			Word w = this->getRandomWord();
			if(getLevel(w.word) == 1 && a > 0)
				{
					wordCollection.push_back(w);
					a--;
					sum++;
				}
			else if(getLevel(w.word) == 2 && b > 0){
					wordCollection.push_back(w);
					b--;
					sum++;
			}
			else{
				wordCollection.push_back(w);
				c--;
				sum++;
			}
		}
	} else {
		printf("Mode %d not available", modeGame);
	}
}

// Function to load data from a text file into a vector of structs
bool WordHandler::loadFromFile(const std::string& filename, std::vector<Word>& word)
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
			break;  // Break if reading fails, assuming end of file or bad format
		}
		// Add the person to the vector
		word.push_back(w);
	}

	// Close the file
	file.close();
	return true;
}

void WordHandler::writeWordsToFile(const std::string& filename, const std::vector<Word>& words)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	// Write each word to the file
	for (const auto& w : words)
	{
		file << w.word << " " << w.totalCount << " " << w.successCount << std::endl;
	}

	// Close the file
	file.close();
}




// Not used yet
bool caseInsensitiveStringCompare(const std::string& str1, const std::string& str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	for (std::string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
		if (tolower(static_cast<unsigned char>(*c1)) != tolower(static_cast<unsigned char>(*c2))) {
			return false;
		}
	}
	return true;
}

std::vector<Word>::iterator WordHandler::findWord(char *ans)
{
	std::string targetWord(ans);
	for (auto it = wordsGlobal.begin(); it != wordsGlobal.end(); ++it)
	{
		if (caseInsensitiveStringCompare(it->word, targetWord))
		{
			return it; // Return an iterator to the found word
		}
	}
	return wordsGlobal.end(); // Word not found
}

// int getLevel(char *word)
// {
//     auto wf = findWord(word);
//     // int percentages =  (wf->successCount) * 100 / (wf->totalCount);

//     // if(percentages == 0 ) return 1;
//     // if(percentages <= 30 && percentages > 0)
//     //     return 3;
//     // else if(percentages >= 50 && percentages < 80 )
//     //     return 2;
//     // else return 1;

// 	return wf.level;
// }

int WordHandler::getLevel(char *word){
	auto wf = findWord(word);
	if(wf != wordsGlobal.end()){
		return -1;
	}
	else return wf->level;
}

void WordHandler::updateWord(char *word, bool correct){
	auto wf = findWord(word);

	wf->totalCount++;
	if(correct) wf->successCount++;
}
