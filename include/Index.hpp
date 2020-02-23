#ifndef INDEX_HPP
#define INDEX_HPP

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

    int totalTerms;
    int totalDocuments;

    bool dirty;

    auto _clean() -> void {
        pairs.clear();

        for (auto e : collectionFrequency)
            pairs.push_back(e);

        sort(pairs.begin(), pairs.end(),
            [=](std::pair<T, int>& a, std::pair<T, int>& b)
            {
                return a.second > b.second;
            }
        );

        dirty = false;
    }
public:
    Index() : totalTerms(0), totalDocuments(0), dirty(false) { }

    auto insert(T term, U documentId) -> void {
        totalTerms++;

        collectionFrequency[term]++;

        #if HAVE_UMAPCONTAINS
        if(!invertedIndex[term].contains(documentId)) {
        #else
        if(invertedIndex[term].count(documentId) == 0) {
        #endif
            documentFrequency[term]++;
        }

        #if HAVE_SETCONTAINS
        if(!documentIds.contains(documentId)) {
        #else
        if(documentIds.count(documentId) == 0) {
        #endif
            totalDocuments++;
            documentIds.insert(documentId);
        }

        invertedIndex[term][documentId]++;

        dirty = true;
    }

    auto getTermCount() const -> int { return totalTerms; };
    auto getDocumentCount() const -> int { return totalDocuments; };

    auto documentFrequencyToWString() const -> std::wstring {
        std::wstringstream wss;

        for(const auto &i : documentFrequency) {
            wss << "docFreq(" << i.first << ") = " << i.second << std::endl;
        }

        return wss.str();
    }

    auto termsSortedByCollectionFrequencyToWString() -> std::wstring {
        std::wstringstream wss;

        if(dirty) {
            _clean();
        }

        for (const auto & e : pairs) {
            wss << "cFreq("<< e.first << ") = " << e.second << std::endl;
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

    auto getDocumentVector(const U & docId, const std::vector<T> & dictionary) -> std::vector<double> {
        std::vector<double> ret;

        for(const auto & term : dictionary) {
            ret.push_back(static_cast<double>(invertedIndex[term][docId]));
        }

        return ret;
    }

    auto getDictionary() -> std::vector<T> {
        std::vector<T> ret;

        for(const auto & el : documentFrequency) {
            ret.push_back(el.first);
        }

        return ret;
    }
};

#endif