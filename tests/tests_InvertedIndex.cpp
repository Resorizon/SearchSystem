#include <gtest/gtest.h>
#include "InvertedIndex.h"

// Вспомогательная функция для сравнения результатов
bool CompareWordCount(const std::vector<std::pair<int, int>>& result, const std::vector<std::pair<int, int>>& expected) {
    return result == expected;
}

// Тест для проверки базовой функциональности
TEST(TestCaseInvertedIndex, TestBasic) {
    InvertedIndex index;

    index.AddDocument("this is a test document");
    index.AddDocument("this document is a test");

    std::vector<std::pair<int, int>> expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("this"), expected));

    expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("is"), expected));

    expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("a"), expected));

    expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("test"), expected));

    expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("document"), expected));
}

// Дополнительный тест для проверки функциональности с другими данными
TEST(TestCaseInvertedIndex, TestBasic2) {
    InvertedIndex index;

    index.AddDocument("another test case");
    index.AddDocument("testing the test case");

    std::vector<std::pair<int, int>> expected = {{0, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("another"), expected));

    expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("test"), expected));

    expected = {{0, 1}, {1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("case"), expected));

    expected = {{1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("testing"), expected));

    expected = {{1, 1}};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("the"), expected));
}

// Тест для проверки случая, когда запрашиваемое слово отсутствует
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    InvertedIndex index;

    index.AddDocument("some random text");
    index.AddDocument("another random document");

    std::vector<std::pair<int, int>> expected = {};
    EXPECT_TRUE(CompareWordCount(index.GetWordCount("missingword"), expected));
}