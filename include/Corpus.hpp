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
#include "PolicyTokenizer001.hpp"

template <class T>
class Corpus {
    std::map<T, Document> documents;
    std::vector<std::wstring> dictionary[4];
    Tokenizer<std::wstring> * tokenizer;
    Index<std::wstring, T> index[4];
public:
    Corpus() {
        tokenizer = new PolicyTokenizer001<std::wstring>();
    }

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
        index[1] = i;
    }

    void setTokenizer(Tokenizer<std::wstring> *tok) {
        tokenizer = tok;
    }

    void setDictionary(std::vector<std::wstring> const & dic ) {
        dictionary[1] = dic;
    };

    std::vector<std::wstring> getDictionary() const {
        return dictionary[1];
    }

    Tokenizer<std::wstring> * getTokenizer() const {
        return tokenizer;
    }

    void buildIndex() {
        buildIndexNGram(1);
    }

    void buildIndexNGram(int n) {
        if(n > 3 || n < 1) {
            return;
        }

        for(const auto &document : documents) {
            auto fullText = File::fileContentToWString(document.second.getMetadata().getFilename());
            auto tokens = tokenizer->tokenize(fullText);

            for(int i = 0; i < tokens.size() - n + 1; i++) {
                std::wstring token;

                token = tokens[i];

                for(int j = 1; j < n; j++) {
                    token += L" ";
                    token += tokens[i + j];
                }

                index[n].insert(token, document.second.getMetadata().getId());
            }
        }

        dictionary[n] = index[n].getDictionary();
    }

    void normalizeDocumentVectors() {
        normalizeDocumentVectorsNGram(1);
    }

    void normalizeDocumentVectorsNGram(int n) {
        if(n > 3 || n < 1) {
            return;
        }

        for(auto &document : documents) {
            document.second.setNormalizedVector(Math::euclideanNormalize(index[n].getDocumentVector(document.first, dictionary[n])));
        }
    }

    void printSummary() {
        printSummaryNGram(1);
    }

    void printSummaryNGram(int n) {
        if(n > 3 || n < 1) {
            return;
        }

        std::cout << "Corpus statistics for " << n << "-gram:" << std::endl;
        std::cout << "-----" << std::endl;
        std::cout << "Total distinct terms = " << index[n].getTermCount() << std::endl;
        std::cout << "Average number of terms per document = ";
        try {
            std::cout << Math::_divide(index[n].getTermCount(), index[n].getDocumentCount()) << std::endl;
        } catch(...) {
            std::cout << "n/a" << std::endl;
        }

        std::cout << "Terms sorted by frequency in the collection:" << std::endl;
        std::wcout << index[n].termsSortedByCollectionFrequencyToWString() << std::endl;
        std::wcout << index[n].termFrequencyByDocumentTopNToWString(10);
        std::wcout << index[n].documentFrequencyToWString() << std::endl;
    }
};

#endif