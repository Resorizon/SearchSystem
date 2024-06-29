#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <mutex>

class InvertedIndex {
public:
    InvertedIndex() = default;

    void AddDocument(const std::string& document);
    std::vector<std::pair<int, int>> GetWordCount(const std::string& word) const;

private:
    std::vector<std::string> documents;
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> index;
    mutable std::mutex mtx;
};

#endif // INVERTEDINDEX_H