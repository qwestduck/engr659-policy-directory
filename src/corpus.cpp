#include "Corpus.hpp"

#include "Document.hpp"
#include "DocumentMetadata.hpp"
#include "File.hpp"
#include "Index.hpp"
#include "Math.hpp"
#include "PolicyTokenizer001.hpp"
#include "baer/Algorithm.hpp"
#include "baer/String.hpp"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

template <class T>
Corpus<T>::Corpus() {
    tokenizer = new PolicyTokenizer001<std::wstring>();
    index.resize(4);
    dictionary.resize(4);
}

template <class T>
auto Corpus<T>::loadFromCSV(const std::string & filename, const std::string & prefix) -> void {
    std::string f;
    T id;

    std::ifstream fin(filename);

    while(fin >> f >> id) {
        addDocument(prefix + f, id);
    }
}

template <class T>
auto Corpus<T>::addDocument(const std::string& filename, T id) -> void {
    DocumentMetadata<T> m(filename, id);
    Document doc;
    doc.setMetadata(m);
    documents[id] = doc;
}

template <class T>
auto Corpus<T>::getDocuments() const -> std::vector<Document> {
    std::vector<Document> ret;

    for (const auto &[id, document] : documents) {
        ret.push_back(document);
    }

    return ret;
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
auto Corpus<T>::isNoiseWord(const std::wstring &word) -> bool {
    return noiseWords.find(word) != noiseWords.end();
}

template <class T>
auto Corpus<T>::buildIndexNGram(int n) -> void {
    if(n >= index.size() || n < 1) {
        return;
    }

    for(const auto &[id, document] : documents) {
        auto fullText = File::fileContentToWString(document.getMetadata().getFilename());
        auto tokens = tokenizer->tokenize(fullText);

        using Iterator = decltype(tokens.begin());

        auto ngrams = baer::algorithm::slidingWindow(tokens, n, [this](Iterator begin, Iterator end, bool &valid) -> auto {
            valid = false;

            if(!isNoiseWord(*begin) && !isNoiseWord(*(end - 1))) {
                valid = true;
            }

            return baer::string::join(begin, end, L" ");
        });

        for(const auto &ngram : ngrams) {
            index[n].insert(ngram, document.getMetadata().getId());
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
    if(n >= index.size() || n < 1) {
        return;
    }

    for(auto &[id, document] : documents) {
        document.setNormalizedVector(Math::euclideanNormalize(index[n].getDocumentVector(id, dictionary[n])));
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
    const int topN = 10;

    if(n >= index.size() || n < 1) {
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
    std::wcout << index[n].termFrequencyByDocumentTopNToWString(topN);
    std::wcout << index[n].documentFrequencyToWString() << std::endl;
}

template <class T>
auto Corpus<T>::printSummaryNGramBrief(int n) -> void {
    for(const auto &[term, frequency] : index[n].termsSortedByCollectionFrequencyTopN(15)) {
        std::wcout << term << std::endl;
    }
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