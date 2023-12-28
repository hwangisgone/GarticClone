#include <unordered_map>
#include <string>
#include <vector>
#include "word_list.hpp"

std::string getRandomString(const std::vector<std::string>& vec) {
    if (vec.empty()) {
        return ""; // Return an empty string if the vector is empty
    }

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random index within the range of the vector size
    std::size_t randomIndex = std::rand() % vec.size();

    // Return the randomly selected string
    return vec[randomIndex];
}

std::string getStringCollection(std::vector<std::string> vec) {
    if (vec.empty()) {
        return ""; // Return an empty string if the vector is empty
    }

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random index within the range of the vector size
    std::size_t randomIndex = std::rand() % vec.size();

    // Return the randomly selected string
    std::string wordChoose = vec[randomIndex];

    // Erase the element at the random index
    vec.erase(vec.begin() + randomIndex);

    return wordChoose;
}