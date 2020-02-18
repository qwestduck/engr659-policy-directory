#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Corpus.hpp"

int main() {
    Corpus<std::string> corpus;

    corpus.loadFromCSV("../data/corpus-metadata.csv", "../data/text/");
    corpus.buildIndex();
    corpus.normalizeDocumentVectors();
    corpus.printSummary();

    return 0;
}