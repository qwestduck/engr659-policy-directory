#include "Corpus.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto main() -> int {
    Corpus<std::string> corpus;

    corpus.loadFromCSV("../data/corpus-metadata.csv", "../data/text/");
    corpus.buildIndexNGram(1);
    corpus.buildIndexNGram(2);
    corpus.buildIndexNGram(3);

    // corpus.normalizeDocumentVectorsNGram(2);
    // corpus.printSimilarDocuments();

    corpus.printSummaryNGramBrief(1);
    corpus.printSummaryNGramBrief(2);
    corpus.printSummaryNGramBrief(3);

    return 0;
}