#include "Document.hpp"

#include "DocumentMetadata.hpp"
#include "Math.hpp"

#include <vector>

Document::Document() { }

double Document::similarity(Document const & b) {
    return Math::dotProduct(normalizedVector, b.getNormalizedVector());
}

void Document::setNormalizedVector(std::vector<double> const & v) {
    normalizedVector = v;
}

std::vector<double> Document::getNormalizedVector() const {
    return normalizedVector;
}

void Document::setMetadata(DocumentMetadata<std::string> const & m) {
    metadata = m;
}

DocumentMetadata<std::string> Document::getMetadata() const {
    return metadata;
}