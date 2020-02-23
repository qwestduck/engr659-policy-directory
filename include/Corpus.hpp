#ifndef CORPUS_HPP
#define CORPUS_HPP

#include "Document.hpp"
#include "Index.hpp"
#include "Tokenizer.hpp"

#include <map>
#include <string>
#include <vector>

/*
# Template types
- T: Document identifier type
  This type should be both orderable and hashable.
*/
template <class T>
class Corpus {
    std::map<T, Document> documents;
    std::vector<std::wstring> dictionary[4];
    Tokenizer<std::wstring> * tokenizer;
    Index<std::wstring, T> index[4];
public:
    Corpus();

    auto loadFromCSV(const std::string filename, const std::string prefix) -> void;

    [[nodiscard]]
    auto getDocuments() const -> std::vector<Document>;

    auto setDictionary(std::vector<std::wstring> const & dic ) -> void;

    [[nodiscard]]
    auto getDictionary() const -> std::vector<std::wstring>;

    auto setTokenizer(Tokenizer<std::wstring> *tok) -> void;

    [[nodiscard]]
    auto getTokenizer() const -> Tokenizer<std::wstring> *;

    auto buildIndex() -> void;
    auto buildIndexNGram(int n) -> void;

    auto normalizeDocumentVectors() -> void;
    auto normalizeDocumentVectorsNGram(int n) -> void;

    [[nodiscard]]
    auto similarityBetween(const Corpus<T> & other) const -> double;

    auto printSummary() -> void;
    auto printSummaryNGram(int n) -> void;
    auto printSimilarDocuments() -> void;
};

#endif