#include "Corpus.hpp"

#include "Document.hpp"
#include "DocumentMetadata.hpp"
#include "File.hpp"
#include "Index.hpp"
#include "Math.hpp"
#include "PolicyTokenizer001.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

template <class T>
Corpus<T>::Corpus() {
    tokenizer = new PolicyTokenizer001<std::wstring>();
}

template <class T>
auto Corpus<T>::loadFromCSV(const std::string & filename, const std::string & prefix) -> void {
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

template <class T>
auto Corpus<T>::getDocuments() const -> std::vector<Document> {
    std::vector<Document> docs;
    for (const auto &d : documents) {
        docs.push_back(d.second);
    }

    return docs;
}

template <class T>
auto Corpus<T>::setTokenizer(Tokenizer<std::wstring> *tok) -> void {
    tokenizer = tok;
}

template <class T>
auto Corpus<T>::setDictionary(std::vector<std::wstring> const & dic ) -> void {
    dictionary[1] = dic;
};

template <class T>
auto Corpus<T>::getDictionary() const -> std::vector<std::wstring> {
    return dictionary[1];
}

template <class T>
auto Corpus<T>::getTokenizer() const -> Tokenizer<std::wstring> * {
    return tokenizer;
}

template <class T>
auto Corpus<T>::buildIndex() -> void {
    buildIndexNGram(1);
}

template <class T>
auto Corpus<T>::buildIndexNGram(int n) -> void {
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

template <class T>
auto Corpus<T>::normalizeDocumentVectors() -> void {
    normalizeDocumentVectorsNGram(1);
}

template <class T>
auto Corpus<T>::normalizeDocumentVectorsNGram(int n) -> void {
    if(n > 3 || n < 1) {
        return;
    }

    for(auto &document : documents) {
        document.second.setNormalizedVector(Math::euclideanNormalize(index[n].getDocumentVector(document.first, dictionary[n])));
    }
}

template <class T>
auto Corpus<T>::similarityBetween(const Corpus<T> & other) const -> double {
    double similaritySum = 0;

	std::vector<Document> a = getDocuments();
	std::vector<Document> b = other.getDocuments();

	for(int i = 0; i < a.size(); i++) {
		similaritySum += Math::dotProduct(a[i].getNormalizedVector(), b[i].getNormalizedVector());
	}

	return Math::divide(similaritySum, static_cast<double>(a.size()));
}

template <class T>
auto Corpus<T>::printSummary() -> void {
    printSummaryNGram(1);
}

template <class T>
auto Corpus<T>::printSummaryNGram(int n) -> void {
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

template <class T>
auto Corpus<T>::printSimilarDocuments() -> void {
    double bestMatchValue = 0;
    double matchValue;
    std::string bestMatchDocId_0;
    std::string bestMatchDocId_1;

    auto docs = getDocuments();
    for (auto it = docs.begin(); (it + 1) != docs.end(); it++) {
        for(auto it2 = it + 1; it2 != docs.end(); it2++) {
            matchValue = it->similarity(*it2);
            if( matchValue > bestMatchValue) {
                bestMatchValue = matchValue;
                bestMatchDocId_0 = it->getMetadata().getId();
                bestMatchDocId_1 = it2->getMetadata().getId();
            }
        }
    }

    std::cout << bestMatchValue << " " << bestMatchDocId_0 << " " << bestMatchDocId_1 << std::endl;
}

template class Corpus<std::string>;