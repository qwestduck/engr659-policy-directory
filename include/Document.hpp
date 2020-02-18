#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <vector>

#include "Math.hpp"

class Document {
    std::vector<double> normalizedVector;
public:
    Document() { }
    double similiarty(Document const & b) {
        return Math::dotProduct(normalizedVector, b.getNormalizedVector());
    }
    std::vector<double> getNormalizedVector() const {
        return normalizedVector;
    }
};

#endif