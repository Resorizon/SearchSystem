#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include "InvertedIndex.h"
#include <string>
#include <vector>
#include <unordered_map>

class SearchServer {
public:
    SearchServer(InvertedIndex& idx, int responses_limit) : index(idx), responses_limit(responses_limit) {}
    
    std::vector<std::vector<std::pair<int, float>>> Search(const std::vector<std::string>& queries) const;

private:
    InvertedIndex& index;
    int responses_limit;

    std::vector<std::pair<int, float>> FindDocuments(const std::string& query) const;
};

#endif // SEARCHSERVER_H