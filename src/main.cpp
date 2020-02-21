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

    // corpus.normalizeDocumentVectorsNGram(2);
    // corpus.printSimilarDocuments();

    corpus.printSummaryNGram(2);

    return 0;
}