#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include "SearchServer.h"

// Вспомогательная функция для сравнения результатов поиска
bool CompareSearchResults(const std::vector<std::pair<int, float>>& result, const std::vector<std::pair<int, float>>& expected) {
    if (result.size() != expected.size()) return false;
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i].first != expected[i].first || std::fabs(result[i].second - expected[i].second) > 1e-5) {
            return false;
        }
    }
    return true;
}

// Вспомогательная функция для вывода результатов поиска
void PrintSearchResults(const std::vector<std::pair<int, float>>& results) {
    for (const auto& [docId, score] : results) {
        std::cout << "DocID: " << docId << ", Score: " << score << std::endl;
    }
}

// Тест для проверки базовой функциональности
TEST(TestCaseSearchServer, TestSimple) {
    InvertedIndex index;
    index.AddDocument("milk milk milk milk water water water");
    index.AddDocument("milk water water");
    index.AddDocument("milk milk milk milk milk water water water water water");
    index.AddDocument("americano cappuccino");

    SearchServer server(index, 5);

    std::vector<std::string> queries = {"milk water", "sugar"};
    auto results = server.Search(queries);

    std::vector<std::pair<int, float>> expected1 = {{2, 1}, {0, 0.7}, {1, 0.3}};
    EXPECT_TRUE(CompareSearchResults(results[0], expected1));

    std::vector<std::pair<int, float>> expected2 = {};
    EXPECT_TRUE(CompareSearchResults(results[1], expected2));
}

// Тест для проверки случая с ограничением результатов до 5
TEST(TestCaseSearchServer, TestTop5) {
    InvertedIndex index;
    index.AddDocument("london is the capital of great britain");
    index.AddDocument("paris is the capital of france");
    index.AddDocument("berlin is the capital of germany");
    index.AddDocument("rome is the capital of italy");
    index.AddDocument("madrid is the capital of spain");
    index.AddDocument("lisboa is the capital of portugal");
    index.AddDocument("bern is the capital of switzerland");
    index.AddDocument("moscow is the capital of russia");
    index.AddDocument("kiev is the capital of ukraine");
    index.AddDocument("minsk is the capital of belarus");
    index.AddDocument("astana is the capital of kazakhstan");
    index.AddDocument("beijing is the capital of china");
    index.AddDocument("tokyo is the capital of japan");
    index.AddDocument("bangkok is the capital of thailand");
    index.AddDocument("welcome to moscow the capital of russia the third rome");
    index.AddDocument("amsterdam is the capital of netherlands");
    index.AddDocument("helsinki is the capital of finland");
    index.AddDocument("oslo is the capital of norway");
    index.AddDocument("stockholm is the capital of sweden");
    index.AddDocument("riga is the capital of latvia");
    index.AddDocument("tallinn is the capital of estonia");
    index.AddDocument("warsaw is the capital of poland");

    SearchServer server(index, 5);

    std::vector<std::string> queries = {"moscow is the capital of russia"};
    auto results = server.Search(queries);

    std::vector<std::pair<int, float>> expected = {{7, 1}, {14, 1}, {0, 0.666666687}, {1, 0.666666687}, {2, 0.666666687}};
    
    std::cout << "Actual Results:" << std::endl;
    PrintSearchResults(results[0]);

    std::cout << "Expected Results:" << std::endl;
    PrintSearchResults(expected);

    EXPECT_TRUE(CompareSearchResults(results[0], expected));
}