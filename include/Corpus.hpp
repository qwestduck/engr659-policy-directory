#ifndef CORPUS_HPP
#define CORPUS_HPP

#include <map>
#include <string>
#include <vector>
#include "Document.hpp"
#include "Index.hpp"
#include "Tokenizer.hpp"

/*
# Template types

T: Document identifier type
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

    void loadFromCSV(const std::string filename, const std::string prefix);

    std::vector<Document> getDocuments() const;

    void setIndex(Index<std::wstring, T> const & i);

    void setDictionary(std::vector<std::wstring> const & dic );
    std::vector<std::wstring> getDictionary() const;

    void setTokenizer(Tokenizer<std::wstring> *tok);
    Tokenizer<std::wstring> * getTokenizer() const;

    void buildIndex();
    void buildIndexNGram(int n);

    void normalizeDocumentVectors();
    void normalizeDocumentVectorsNGram(int n);

    void printSummary();
    void printSummaryNGram(int n);
    void printSimilarDocuments();
};

#endif