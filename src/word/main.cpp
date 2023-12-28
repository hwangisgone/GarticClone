#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> garticWords;

string underscoreConvert(string str) {
	string ud(str.size(), '_');
	return ud;
}

int main() {
	ifstream file("../src/word/wordlist.txt");

	// Check if the file is open
    if (!file.is_open()) {  
        cerr << "Error opening file.\n";
        return 1;
    }

    string word;
    while (file >> word) {
    	garticWords.push_back(word);
    }

    file.close();

    // Random time
    srand(static_cast<unsigned int>(time(nullptr)));

    size_t randomi = rand() % garticWords.size();

    string chosenWord = garticWords[randomi];
    cout << "Word of the day: " << chosenWord;
    cout << " " << chosenWord.size();
    cout << " " << underscoreConvert(chosenWord) << '\n';
    
    printf("Success open file\n");

    return 0;
}