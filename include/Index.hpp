#ifndef INDEX_HPP
#define INDEX_HPP

#include <codecvt>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

template <class T, class U>
class Index {
    std::unordered_map<std::wstring, int> collectionFrequency;
    std::map<std::wstring, int> documentFrequency;
    std::unordered_map<std::wstring, std::unordered_map<U, int>> invertedIndex;

    std::set<U> documentIds;
    std::vector<std::pair<std::wstring, int>> pairs;

    int totalTerms;
    int totalDocuments;

    bool dirty;

    void _clean() {
        pairs.clear();

        for (auto e : collectionFrequency)
            pairs.push_back(e);

        sort(pairs.begin(), pairs.end(),
            [=](std::pair<std::wstring, int>& a, std::pair<std::wstring, int>& b)
            {
                return a.second > b.second;
            }
        );

        dirty = false;
    }
public:
    Index() : totalTerms(0), totalDocuments(0), dirty(false) { }

    void insert(T term, U documentId) {
        totalTerms++;

        collectionFrequency[term]++;

        if(!invertedIndex[term].contains(documentId)) {
            documentFrequency[term]++;
        }

        if(!documentIds.contains(documentId)) {
            totalDocuments++;
            documentIds.insert(documentId);
        }

        invertedIndex[term][documentId]++;

        dirty = true;
    }

    int getTermCount() const { return totalTerms; };
    int getDocumentCount() const { return totalDocuments; };

    std::wstring documentFrequencyToWString() const {
        std::wstringstream wss;

        for(const auto &i : documentFrequency) {
            wss << "docFreq(" << i.first << ") = " << i.second << std::endl;
        }

        return wss.str();
    }

    std::wstring termsSortedByCollectionFrequencyToWString() {
        std::wstringstream wss;

        if(dirty) {
            _clean();
        }

        for (const auto & e : pairs) {
            wss << "cFreq("<< e.first << ") = " << e.second << std::endl;
        }

        return wss.str();
    }

    std::wstring termFrequencyByDocumentTopNToWString(int n) {
        std::wstringstream wss;

        if(dirty) {
            _clean();
        }

        wss << "\t";

        for(int i = 0; i < n; i++) {
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
};

#endif