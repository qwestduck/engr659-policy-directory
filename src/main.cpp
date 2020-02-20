#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Corpus.hpp"

int main() {
    Corpus<std::string> corpus;

    corpus.loadFromCSV("../data/corpus-metadata.csv", "../data/text/");
    corpus.buildIndexNGram(2);
    corpus.normalizeDocumentVectorsNGram(2);

    // Document similarity
    /*
    double bestMatchValue = 0;
    double matchValue;
    std::string bestMatchDocId_0;
    std::string bestMatchDocId_1;

    std::vector<Document> docs;
    docs = corpus.getDocuments();
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
    */

    corpus.printSummaryNGram(2);

    return 0;
}