#ifndef DOCUMENTMETADATA_HPP
#define DOCUMENTMETADATA_HPP

#include <string>

template <class T>
class DocumentMetadata {
    std::string filename;
    T id;
public:
    DocumentMetadata () {}
    DocumentMetadata(std::string filename, T id) : filename(filename), id(id) { }
    auto getFilename() const -> std::string { return filename; }
    auto getId() const -> T { return id; }
};

#endif