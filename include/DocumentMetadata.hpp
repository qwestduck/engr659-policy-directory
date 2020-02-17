#ifndef DOCUMENTMETADATA_HPP
#define DOCUMENTMETADATA_HPP

#include <string>

class DocumentMetadata {
    std::string filename;
    int id;
public:
    DocumentMetadata(std::string filename, int id) : filename(filename), id(id) { }
    std::string getFilename() const { return filename; }
    int getId() const { return id; }
};

#endif