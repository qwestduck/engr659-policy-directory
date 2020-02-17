#ifndef CORPUS_HPP
#define CORPUS_HPP

#include <string>
#include <vector>
#include "DocumentMetadata.hpp"

class Corpus {
std::vector<DocumentMetadata> metadata;
public:
    Corpus() { }

    void loadFromCSV(const std::string filename, const std::string prefix) {
        std::string f;
        int id = 0;

        std::ifstream fin(filename);

        while(fin >> f) {
            DocumentMetadata d(prefix + f, id);
            metadata.push_back(d);

            id++;
        }
    }

    std::vector<DocumentMetadata> getMetadata() { return metadata; };
};

#endif