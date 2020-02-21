#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "DocumentMetadata.hpp"

#include <vector>

class Document {
    std::vector<double> normalizedVector;
    DocumentMetadata<std::string> metadata;
public:
    Document();
    double similarity(Document const & b);

    void setNormalizedVector(std::vector<double> const & v);
    std::vector<double> getNormalizedVector() const;

    void setMetadata(DocumentMetadata<std::string> const & m);
    DocumentMetadata<std::string> getMetadata() const;
};

#endif