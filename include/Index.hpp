#ifndef INDEX_HPP
#define INDEX_HPP

#include "Math.hpp"

#include <cmath>
#include <codecvt>
#include <locale>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

template <class T, class U>
class Index {
    std::unordered_map<T, int> collectionFrequency;
    std::map<T, int> documentFrequency;
    std::unordered_map<T, std::unordered_map<U, int>> invertedIndex;

    std::set<U> documentIds;
    std::vector<std::pair<T, int>> pairs;

    std::unordered_map<U, std::unordered_map<T, int>> docFirstOf;
    std::unordered_map<U, int> termsProcessedByDocument;

    int totalTerms = 0;
    int totalDocuments = 0;

    bool dirty = false;

    auto _clean() -> void {
        pairs.clear();

        for (const auto& e : collectionFrequency) {
            pairs.push_back(e);
        }

        sort(pairs.begin(), pairs.end(),
            [=](std::pair<T, int>& a, std::pair<T, int>& b)
            {
                return a.second > b.second;
            }
        );

        dirty = false;
    }
public:
    Index() = default;

    auto insert(T term, U documentId) -> void {
        totalTerms++;

        collectionFrequency[term]++;

        if(docFirstOf[documentId].count(term) == 0) {
            docFirstOf[documentId][term] = termsProcessedByDocument[documentId];
        }

        termsProcessedByDocument[documentId]++;

        if(invertedIndex[term].count(documentId) == 0) {
            documentFrequency[term]++;
        }

        if(documentIds.count(documentId) == 0) {
            totalDocuments++;
            documentIds.insert(documentId);
        }

        invertedIndex[term][documentId]++;

        dirty = true;
    }

    [[nodiscard]]
    auto getTermCount() const -> int { return totalTerms; };

    [[nodiscard]]
    auto getDocumentCount() const -> int { return totalDocuments; };

    [[nodiscard]]
    auto documentFrequencyToWString() const -> std::wstring {
        std::wstringstream wss;

        for(const auto &[term, frequency] : documentFrequency) {
            wss << "docFreq(" << term << ") = " << frequency << std::endl;
        }

        return wss.str();
    }

    auto termsSortedByCollectionFrequencyTopN(int n) -> std::vector<std::pair<T, int>> {
        std::vector<std::pair<T, int>> ret;

        if(dirty) {
            _clean();
        }

        for(int i = 0; (i < n) && (i < pairs.size()); i++) {
            ret.push_back(pairs.at(i));
        }

        return ret;
    }

    auto termsSortedByCollectionFrequencyToWString() -> std::wstring {
        std::wstringstream wss;

        if(dirty) {
            _clean();
        }

        for (const auto &[term, frequency] : pairs) {
            wss << "cFreq("<< term << ") = " << frequency << std::endl;
        }

        return wss.str();
    }

    auto termFrequencyByDocumentTopNToWString(int n) -> std::wstring {
        std::wstringstream wss;

        if(dirty) {
            _clean();
        }

        wss << "\t";

        for(int i = 0; (i < n) && (i < pairs.size()) ; i++) {
            wss << pairs[i].first << "\t";
        }

        wss << std::endl;

        for(const auto &d : documentIds) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

            wss << conv.from_bytes(d) << "\t";
            for(int i = 0; i < n; i++) {
                wss << invertedIndex[pairs[i].first][d] << "\t";
            }

            wss << std::endl;
        }

        return wss.str();
    }

    [[nodiscard]]
    auto getDocumentVector(const U & docId, const std::vector<T> & dictionary) const -> std::vector<double> {
        std::vector<double> ret;

        for(const auto & term : dictionary) {
            // not an indexed term?
            if(invertedIndex.find(term) == invertedIndex.end()) {
                ret.push_back(0.0);

                continue;
            }

            // term not found in document?
            if(auto it = invertedIndex.at(term).find(docId); it == invertedIndex.at(term).end()) {
                ret.push_back(0.0);
            } else {
                ret.push_back(static_cast<double>((*it).second));
            }
        }

        return ret;
    }

    [[nodiscard]]
    auto getIdfVector(const std::vector<std::wstring> & dictionary) const -> std::vector<double> {
        std::vector<double> ret;

        ret.reserve(dictionary.size());
        for(const auto & term : dictionary) {
            ret.push_back(
                log(
                    Math::_divide(totalDocuments, documentFrequency.at(term))
                )
            );
        }

        return ret;
    }

    auto positionVector(U docId, const std::vector<std::wstring> & dictionary) const -> std::vector<double> {
        std::vector<double> ret;

        for(const auto & term : dictionary) {
            try {
                ret.push_back(static_cast<double>(docFirstOf.at(docId).at(term)));
            } catch(const std::out_of_range & e) {
                ret.push_back(-1);
            }
        }

        return ret;
    }

    [[nodiscard]]
    auto getDictionary() const -> std::vector<T> {
        std::vector<T> ret;

        for(const auto &[term, frequency] : documentFrequency) {
            ret.push_back(term);
        }

        return ret;
    }
};

#endif