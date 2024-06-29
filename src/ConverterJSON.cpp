#include "ConverterJSON.h"
#include "Utils.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <regex>

json ConverterJSON::readJSONFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("config file is missing");
    }
    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("JSON parse error in file " + filename + ": " + e.what());
    } catch (const json::type_error& e) {
        throw std::runtime_error("JSON type error in file " + filename + ": " + e.what());
    } catch (...) {
        throw std::runtime_error("Unknown error occurred while reading file " + filename);
    }
    return j;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() const {
    json config = readJSONFile(Constants::CONFIG_FILE);

    if (!config.contains(Constants::CONFIG)) {
        throw std::runtime_error("config file is empty");
    }
    if (!config.contains(Constants::FILES)) {
        throw std::runtime_error("no path to files");
    }

    std::vector<std::string> textDocuments;
    for (const auto& filePath : config[Constants::FILES]) {
        std::string path = filePath.get<std::string>();
        std::ifstream textFile(path);
        if (!textFile.is_open()) {
            std::cerr << "Could not open file: " << path << std::endl;
            continue;
        }
        std::string text((std::istreambuf_iterator<char>(textFile)), std::istreambuf_iterator<char>());

        std::istringstream iss(text);
        std::string word;
        int wordCount = 0;
        bool validFile = true;
        while (iss >> word) {
            if (word.length() > 100 || !isValidWord(word)) {
                std::cerr << "Invalid word in file: " << path << std::endl;
                validFile = false;
                break;
            }
            ++wordCount;
            if (wordCount > 1000) {
                std::cerr << "File exceeds maximum word count of 1000 words: " << path << std::endl;
                validFile = false;
                break;
            }
        }
        if (validFile) {
            textDocuments.push_back(text);
        }
    }
    return textDocuments;
}

std::vector<std::string> ConverterJSON::GetRequests() const {
    json requests = readJSONFile(Constants::REQUESTS_FILE);

    std::vector<std::string> queries;
    if (!requests.contains(Constants::REQUESTS)) {
        std::cerr << "Invalid or missing 'requests' key in requests.json" << std::endl;
        return queries;
    }

    for (const auto& request : requests[Constants::REQUESTS]) {
        std::string query = request.get<std::string>();
        std::istringstream iss(query);
        std::string word;
        bool validRequest = true;
        while (iss >> word) {
            if (!isValidWord(word)) {
                std::cerr << "Invalid word in request: " << query << std::endl;
                validRequest = false;
                break;
            }
        }
        if (validRequest) {
            queries.push_back(query);
        }
    }
    return queries;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) const {
    json answerJSON;

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string requestKey = "request" + std::to_string(i + 1);
        if (answers[i].empty()) {
            answerJSON[Constants::ANSWERS][requestKey][Constants::RESULT] = false;
        } else {
            answerJSON[Constants::ANSWERS][requestKey][Constants::RESULT] = true;
            if (answers[i].size() > 1) {
                answerJSON[Constants::ANSWERS][requestKey][Constants::RELEVANCE] = json::array();
                for (const auto& answer : answers[i]) {
                    answerJSON[Constants::ANSWERS][requestKey][Constants::RELEVANCE].push_back({
                        {Constants::DOCID, answer.first}, {Constants::RANK, answer.second}
                    });
                }
            } else {
                for (const auto& answer : answers[i]) {
                    answerJSON[Constants::ANSWERS][requestKey][Constants::DOCID] = answer.first;
                    answerJSON[Constants::ANSWERS][requestKey][Constants::RANK] = answer.second;
                }
            }
        }
    }

    std::ofstream outFile(Constants::ANSWERS_FILE);
    if (!outFile.is_open()) {
        std::cerr << "Could not open file for writing: answers.json" << std::endl;
        return;
    }
    outFile << answerJSON.dump(4);
}

int ConverterJSON::GetResponsesLimit() const {
    json config = readJSONFile(Constants::CONFIG_FILE);

    if (!config.contains(Constants::CONFIG)) {
        throw std::runtime_error("config file is empty [config]");
    }

    if (!config[Constants::CONFIG].contains(Constants::MAX_RESPONSES)) {
        throw std::runtime_error("Invalid or missing 'max_responses' key in config.json");
    }

    return config[Constants::CONFIG][Constants::MAX_RESPONSES].get<int>();
}

std::string ConverterJSON::GetAppName() const {
    json config = readJSONFile(Constants::CONFIG_FILE);

    if (!config.contains(Constants::CONFIG) || !config[Constants::CONFIG].contains(Constants::NAME)) {
        throw std::runtime_error("config file is empty [name]");
    }

    return config[Constants::CONFIG][Constants::NAME].get<std::string>();
}