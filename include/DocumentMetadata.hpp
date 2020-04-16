#ifndef DOCUMENTMETADATA_HPP
#define DOCUMENTMETADATA_HPP

#include <string>
#include <utility>

template <class T>
class DocumentMetadata {
    std::string filename;
    T id;
public:
    DocumentMetadata () = default;
    DocumentMetadata(std::string filename, T id) : filename(std::move(filename)), id(std::move(id)) { }

    [[nodiscard]]
    auto getFilename() const -> std::string { return filename; }

    [[nodiscard]]
    auto getId() const -> T { return id; }
};

#endif