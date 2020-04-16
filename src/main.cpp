#include "baer/Algorithm.hpp"
#include "Corpus.hpp"
#include "Math.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto main() -> int {
    Corpus<std::string> corpus;

    corpus.loadFromCSV("../data/corpus-metadata.csv", "../data/text/");

    const int MAX_NGRAM_SIZE = 3;
    const int TOPN = 10;
    const double TFIDF_WEIGHT = 0.9;

    using index_t = Index<std::wstring, std::string>;
    using dictionary_t = std::vector<std::wstring>;
    using idfVectors_t = std::vector<double>;

    std::vector<index_t> indices;
    std::vector<dictionary_t> dictionaries;
    std::vector<idfVectors_t> idfVectors;

    for(int i = 0; i < MAX_NGRAM_SIZE; i++) {
        indices.push_back(corpus.buildIndexNGram(i + 1));
        dictionaries.push_back(indices[i].getDictionary());
        idfVectors.push_back(indices[i].getIdfVector(dictionaries[i]));
    }

    for(const auto & doc : corpus.getDocuments()) {
        auto docId = doc.getMetadata().getId();

        for(int i = 0; i < MAX_NGRAM_SIZE; i++) {
            auto tfVector =  indices[i].getDocumentVector(docId, dictionaries[i]);
            auto posVector = indices[i].positionVector(docId, dictionaries[i]);

            auto candidates = baer::algorithm::topN_iv(
                Math::vectorAdd(
                    Math::scalarProduct(
                        Math::hadamardProduct(
                            tfVector, idfVectors[i]
                        ), TFIDF_WEIGHT
                    ),
                    Math::scalarProduct(posVector, 1 - TFIDF_WEIGHT)
                ), TOPN
            );

            for(const auto &[key, value] : candidates) {
                std::wcout << dictionaries[i][key] << " " << value << std::endl;
            }
        }
    }

    return 0;
}