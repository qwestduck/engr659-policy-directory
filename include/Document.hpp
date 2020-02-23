#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "DocumentMetadata.hpp"

#include <vector>

class Document {
    std::vector<double> normalizedVector;
    DocumentMetadata<std::string> metadata;
public:
    Document();
    [[nodiscard]]
    auto similarity(Document const & b) -> double;

    auto setNormalizedVector(std::vector<double> const & v) -> void;

    [[nodiscard]]
    auto getNormalizedVector() const -> std::vector<double>;

    auto setMetadata(DocumentMetadata<std::string> const & m) -> void;

    [[nodiscard]]
    auto getMetadata() const -> DocumentMetadata<std::string>;
};

#endif