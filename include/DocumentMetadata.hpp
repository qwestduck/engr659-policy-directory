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
    std::string getFilename() const { return filename; }
    T getId() const { return id; }
};

#endif