#ifndef CORPUS_HPP
#define CORPUS_HPP

#include "Document.hpp"
#include "Index.hpp"
#include "Tokenizer.hpp"

#include <map>
#include <set>
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
    std::vector<std::vector<std::wstring>> dictionary;
    const std::set<std::wstring> noiseWords {
      L"the", L"of", L"to", L"and", L"or", L"for", L"in", L"be",
      L"is", L"are", L"that", L"will", L"by", L"with", L"as", L"may", L"on", L"an",
      L"must", L"this", L"from", L"any", L"all", L"at", L"if", L"have", L"it", L"has",
      L"such", L"can", L"than", L"through", L"they", L"but", L"also", L"and/or",
      L"been", L"those", L"do", L"their", L"into", L"so", L"then", L"he", L"he/she"
    };
    Tokenizer<std::wstring> * tokenizer;
    std::vector<Index<std::wstring, T>> index;

    auto isNoiseWord(const std::wstring &word) -> bool;
public:
    Corpus();

    auto loadFromCSV(const std::string & filename, const std::string & prefix) -> void;
    auto addDocument(const std::string& filename, T id) -> void;

    [[nodiscard]]
    auto getDocuments() const -> std::vector<Document>;

    auto setDictionary(std::vector<std::wstring> const & dic ) -> void;

    [[nodiscard]]
    auto getDictionary() const -> std::vector<std::wstring>;

    auto setTokenizer(Tokenizer<std::wstring> *tok) -> void;

    [[nodiscard]]
    auto getTokenizer() const -> Tokenizer<std::wstring> *;

    auto buildIndex() -> Index<std::wstring, T>;
    auto buildIndexNGram(int n) -> Index<std::wstring, T>;

    auto normalizeDocumentVectors() -> void;
    auto normalizeDocumentVectorsNGram(int n) -> void;

    [[nodiscard]]
    auto similarityBetween(const Corpus<T> & other) const -> double;

    auto printSummary() -> void;
    auto printSummaryNGram(int n) -> void;
    auto printSummaryNGramBrief(int n) -> void;
    auto printSimilarDocuments() -> void;
};

#endif