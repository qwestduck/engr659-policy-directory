#ifndef CORPUS_HPP
#define CORPUS_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Document.hpp"
#include "DocumentMetadata.hpp"
#include "File.hpp"
#include "Index.hpp"
#include "WhitespaceTokenizer.hpp"

template <class T>
class Corpus {
    std::map<T, Document> documents;
    Tokenizer<std::wstring> tokenizer;
    Index<std::wstring, T> index;
public:
    Corpus() : tokenizer(WhitespaceTokenizer<std::wstring>()) { }

    void loadFromCSV(const std::string filename, const std::string prefix) {
        std::string f;
        T id;

        std::ifstream fin(filename);

        while(fin >> f >> id) {
            DocumentMetadata<T> m(prefix + f, id);
            Document doc;
            doc.setMetadata(m);
            documents[id] = doc;
        }
    }

    std::vector<Document> getDocuments() const {
        std::vector<Document> docs;
        for (const auto &d : documents) {
            docs.push_back(d.second);
        }

        return docs;
    }

    void setIndex(Index<std::wstring, T> const & i) {
        index = i;
    }

    void setTokenizer(Tokenizer<std::wstring> & tok) {
        tokenizer = tok;
    }

    Tokenizer getTokenizer() const {
        return tokenizer;
    }

    void buildIndex() {
        for(const auto &document : documents) {
            auto fullText = File::fileContentToWString(document.second.getMetadata().getFilename());

            for(const auto &term : tokenizer.tokenize(fullText)) {
                index.insert(term, document.second.getMetadata().getId());
            }
        }
    }

    void normalizeDocumentVectors() {
        for(auto &document : documents) {
            document.second.setNormalizedVector(Math::euclideanNormalize(index.getDocumentVector(document.first)));
        }
    }

    void printSummary() {
        std::cout << "Corpus statistics:" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "Total distinct words = " << index.getTermCount() << std::endl;
        std::cout << "Average number of words per document = ";
        try {
            std::cout << Math::_divide(index.getTermCount(), index.getDocumentCount()) << std::endl;
        } catch(...) {
            std::cout << "n/a" << std::endl;
        }

        std::cout << "Terms sorted by frequency in the collection:" << std::endl;
        std::wcout << index.termsSortedByCollectionFrequencyToWString() << std::endl;
        std::wcout << index.termFrequencyByDocumentTopNToWString(10);
        std::wcout << index.documentFrequencyToWString() << std::endl;
    }
};

#endif