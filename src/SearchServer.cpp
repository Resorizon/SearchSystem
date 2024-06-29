#include "SearchServer.h"
#include "Utils.h"
#include <sstream>
#include <algorithm>
#include <cmath>

std::vector<std::pair<int, float>> SearchServer::FindDocuments(const std::string& query) const {
    std::unordered_map<int, float> docScores;
    std::istringstream iss(query);
    std::string word;

    while (iss >> word) {
        if (isValidWord(word)) {
            for (const auto& [docId, count] : index.GetWordCount(word)) {
                docScores[docId] += count;
            }
        }
    }

    if (docScores.empty()) {
        return {};
    }

    float maxScore = std::max_element(
        docScores.begin(), docScores.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        })->second;

    std::vector<std::pair<int, float>> sortedDocs;
    for (const auto& [docId, score] : docScores) {
        sortedDocs.emplace_back(docId, score / maxScore);
    }

    // Измененная функция сортировки
    std::sort(sortedDocs.begin(), sortedDocs.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.second != rhs.second) {
            return lhs.second > rhs.second;
        }
        return lhs.first < rhs.first;
    });

    if (sortedDocs.size() > responses_limit) {
        sortedDocs.resize(responses_limit);
    }

    return sortedDocs;
}

std::vector<std::vector<std::pair<int, float>>> SearchServer::Search(const std::vector<std::string>& queries) const {
    std::vector<std::vector<std::pair<int, float>>> results;
    for (const auto& query : queries) {
        results.push_back(FindDocuments(query));
    }
    return results;
}