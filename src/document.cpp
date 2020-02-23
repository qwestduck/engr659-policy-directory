#include "Document.hpp"

#include "DocumentMetadata.hpp"
#include "Math.hpp"

#include <vector>

Document::Document() { }

auto Document::similarity(Document const & b) -> double {
    return Math::dotProduct(normalizedVector, b.getNormalizedVector());
}

auto Document::setNormalizedVector(std::vector<double> const & v) -> void {
    normalizedVector = v;
}

auto Document::getNormalizedVector() const -> std::vector<double> {
    return normalizedVector;
}

auto Document::setMetadata(DocumentMetadata<std::string> const & m) -> void {
    metadata = m;
}

auto Document::getMetadata() const -> DocumentMetadata<std::string> {
    return metadata;
}