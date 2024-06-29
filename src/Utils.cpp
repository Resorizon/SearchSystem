#include "Utils.h"
#include <algorithm>
#include <cctype>

bool isValidWord(const std::string& word) {
    return std::all_of(word.begin(), word.end(), [](char c) {
        return std::isalpha(c);
    });
}