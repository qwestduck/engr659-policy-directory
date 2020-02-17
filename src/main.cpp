#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Corpus.hpp"
#include "Index.hpp"
#include "WhitespaceTokenizer.hpp"

inline std::wstring fileContentToWString(std::string filename) {
    std::wifstream fin(filename);
    std::wstringstream buffer;
    buffer << fin.rdbuf();

    return buffer.str();
}

inline double divide(double num, double den) 
{ 
    if (den == 0.0) { 
        throw std::overflow_error("Division by zero"); 
    } 
  
    return (num / den);
}

inline double _divide(int num, int den) {
    return divide(static_cast<double>(num), static_cast<double>(den));
}

int main() {
    Corpus corpus;
    Index<std::wstring, int> index;
    WhitespaceTokenizer<std::wstring> tokenizer;

    corpus.loadFromCSV("../data/corpus-metadata.csv", "../data/text/");

    for(const auto &document : corpus.getMetadata()) {
        auto fullText = fileContentToWString(document.getFilename());

        for(const auto &term : tokenizer.tokenize(fullText)) {
            index.insert(term, document.getId());
        }
    }

    std::cout << "Corpus statistics:" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Total distinct words = " << index.getTermCount() << std::endl;
    std::cout << "Average number of words per document = ";
    try {
        std::cout << _divide(index.getTermCount(), index.getDocumentCount()) << std::endl;
    } catch(...) {
        std::cout << "n/a" << std::endl;
    }

    std::cout << "Terms sorted by frequency in the collection:" << std::endl;
    std::wcout << index.termsSortedByCollectionFrequencyToWString() << std::endl;
    std::wcout << index.termFrequencyByDocumentTopNToWString(10);
    std::wcout << index.documentFrequencyToWString() << std::endl;

    return 0;
}