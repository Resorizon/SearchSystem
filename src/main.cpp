#include <iostream>
#include <thread>
#include <future>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include "Constants.h"

void IndexDocument(InvertedIndex& index, const std::string& document) {
    index.AddDocument(document);
}

int main() {
    try {
        ConverterJSON converter;

        std::string appName = converter.GetAppName();
        std::cout << "Starting " << appName << std::endl;

        int responses_limit = converter.GetResponsesLimit();

        InvertedIndex index;
        SearchServer searchServer(index, responses_limit);

        auto documents = converter.GetTextDocuments();
        std::vector<std::future<void>> futures;

        for (const auto& doc : documents) {
            futures.push_back(std::async(std::launch::async, IndexDocument, std::ref(index), std::cref(doc)));
        }

        for (auto& future : futures) {
            future.get();
        }

        auto queries = converter.GetRequests();

        auto answers = searchServer.Search(queries);

        converter.putAnswers(answers);

        std::cout << "The search is completed and the answers are written to the " << Constants::ANSWERS_FILE << " file" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}