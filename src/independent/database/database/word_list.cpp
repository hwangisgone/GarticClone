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

Word WordHanlder::getRandomWord(std::vector<Word>& words) {
	if (words.empty()) {
		return {"", 0, 0}; // Return an empty string if the vector is empty
	}

	// multithreading problem if use wordsGlobal
	std::shuffle(wordsCollection.begin(), wordsCollection.end(), gameRng);

	// Seed the random number generator with the current time
	std::srand(std::time(0));

	// Generate a random index within the range of the vector size
	std::size_t randomIndex = std::rand() % words.size();

	// Return the randomly selected string
	return words[randomIndex];
}


Word WordHanlder::getRandomAndRemove(std::vector<Word>& words) {
	if (words.empty()) {
		// Handle the case where the vector is empty
		return {"", 0, 0};
	}

	std::srand(std::time(0));

	// Generate a random index within the range of the vector size
	std::size_t randomIndex = std::rand() % words.size();

	// Get the randomly selected word
	Word randomWord = words[randomIndex];

	// Remove the word at the random index from the vector
	words.erase(words.begin() + randomIndex);

	return randomWord;
}

void WordHanlder::setMode(int modeGame){
	Word randomWord ;
	// if(modeGame == 0){
	// 	// 6 word | 3 easy, 2 medium, 1 hard
	// 	// 6 word - easy all

	// 	for( int i = 1 ; i<= 6 ; i++){
	// 		// get i random word
	// 		// push to vector collection

	// 		// get easy word from WordHandler->easy ?
	// 		randomWord = getRandomWord(easy);
	// 		wordCollection.push_back(randomWord);
	// 	}

	// 	// for( int i = 1 ; i<= 2; i++){
	// 	//  randomWord = getRandomWord(medium);
	// 	//  wordCollection.push_back(randomWord);
	// 	// }

	// 	// randomWord = getRandomWord(hard);
	// 	// wordCollection.push_back(randomWord);

	// }
	// else if(modeGame == 1){ 
	// 	// 8 word | 2 easy, 3 medium, 3 hard
	// 	for( int i = 1 ; i<= 2 ; i++){
	// 		// get easy word from WordHandler->easy ?
	// 		randomWord = getRandomWord(easy);
	// 		wordCollection.push_back(randomWord);
	// 	}

	// 	for ( int i = 1 ; i<= 3 ; i++){
	// 		// get easy word from WordHandler->medium ?
	// 		randomWord = getRandomWord(medium);
	// 		wordCollection.push_back(randomWord);
	// 	}

	// 	for( int i = 1 ; i <= 3 ; i++){
	// 		// get easy word from WordHandler->hard ?
	// 		randomWord = getRandomWord(hard);
	// 		wordCollection.push_back(randomWord);
	// 	}

	// } else if (modeGame == 2) {
	// 	// 10 word | 2 easy, 3 medium, 5 hard
	// 	for( int i = 1 ; i<= 2 ; i++){
	// 		// get easy word from WordHandler->easy ?
	// 		randomWord = getRandomWord(easy);
	// 		wordCollection.push_back(randomWord);
	// 	}

	// 	for ( int i = 1 ; i<= 3 ; i++){
	// 		// get easy word from WordHandler->medium ?
	// 		randomWord = getRandomWord(medium);
	// 		wordCollection.push_back(randomWord);
	// 	}

	// 	for( int i = 1 ; i <= 5 ; i++){
	// 		// get easy word from WordHandler->hard ?
	// 		randomWord = getRandomWord(hard);
	// 		wordCollection.push_back(randomWord);
	// 	}
	// } else {
	// 	printf("Mode %d not available", modeGame);
	// }
}

// Function to load data from a text file into a vector of structs
bool WordHanlder::loadFromFile(const std::string& filename, std::vector<Word>& word)
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

void WordHanlder::writeWordsToFile(const std::string& filename, const std::vector<Word>& words)
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

// std::vector<Word>::iterator WordHanlder::findWord(char *ans)
// {
// 	std::string targetWord(ans);
// 	for (auto it = words.begin(); it != words.end(); ++it)
// 	{
// 		if (caseInsensitiveStringCompare(it->word, targetWord))
// 		{
// 			return it; // Return an iterator to the found word
// 		}
// 	}
// 	return words.end(); // Word not found
// }

// int getLevel(std::vector<Word>& words, char *word)
// {
//     auto wf = findWord(words, word);
//     int percentages =  (wf->successCount) * 100 / (wf->totalCount);

//     if(percentages == 0 ) return 1;
//     if(percentages <= 30 && percentages > 0)
//         return 3;
//     else if(percentages >= 50 && percentages < 80 )
//         return 2;
//     else return 1;
// }

int WordHanlder::getPoint(const Word& word){
	if (word.level == 1) return 30;
	else if (word.level == 2) return 50;
	else return 80;
}

// void WordHanlder::updateWord(char *word, bool correct){
// 	 auto wf = findWord(words, word);

// 	 wf->totalCount++;
// 	 if(correct) wf->successCount++;
// }
