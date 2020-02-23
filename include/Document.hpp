#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "DocumentMetadata.hpp"

#include <vector>

class Document {
    std::vector<double> normalizedVector;
    DocumentMetadata<std::string> metadata;
public:
    Document();
    auto similarity(Document const & b) -> double;

    auto setNormalizedVector(std::vector<double> const & v) -> void;
    auto getNormalizedVector() const -> std::vector<double>;

    auto setMetadata(DocumentMetadata<std::string> const & m) -> void;
    auto getMetadata() const -> DocumentMetadata<std::string>;
};

#endif