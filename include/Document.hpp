#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <vector>

#include "DocumentMetadata.hpp"
#include "Math.hpp"

class Document {
    std::vector<double> normalizedVector;
    DocumentMetadata<std::string> metadata;
public:
    Document() { }
    double similiarty(Document const & b) {
        return Math::dotProduct(normalizedVector, b.getNormalizedVector());
    }

    void setNormalizedVector(std::vector<double> const & v) {
        normalizedVector = v;
    }

    std::vector<double> getNormalizedVector() const {
        return normalizedVector;
    }

    void setMetadata(DocumentMetadata<std::string> const & m) {
        metadata = m;
    }

    DocumentMetadata<std::string> getMetadata() const {
        return metadata;
    }
};

#endif