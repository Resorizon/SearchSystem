#include "InvertedIndex.h"
#include "Utils.h"
#include <sstream>
#include <algorithm>

void InvertedIndex::AddDocument(const std::string& document) {
    std::lock_guard<std::mutex> lock(mtx);  // Блокировка мьютекса
    int docId = documents.size();
    documents.push_back(document);

    std::istringstream iss(document);
    std::string word;
    std::unordered_map<std::string, int> wordCount;

    while (iss >> word) {
        if (isValidWord(word)) {
            ++wordCount[word];
        }
    }

    for (const auto& [word, count] : wordCount) {
        index[word].emplace_back(docId, count);
    }
}

std::vector<std::pair<int, int>> InvertedIndex::GetWordCount(const std::string& word) const {
    std::lock_guard<std::mutex> lock(mtx);
    if (index.find(word) != index.end()) {
        return index.at(word);
    }
    return {};
}