#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConverterJSON {
public:
    json readJSONFile(const std::string& filename) const;
    std::vector<std::string> GetTextDocuments() const;
    std::vector<std::string> GetRequests() const;
    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) const;
    int GetResponsesLimit() const;
    std::string GetAppName() const;
};

#endif // CONVERTERJSON_H