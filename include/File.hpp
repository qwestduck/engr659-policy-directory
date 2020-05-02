#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <sstream>
#include <string>

class File {
public:
    File() = default;

    [[nodiscard]]
    static auto fileContentToWString(const std::string& filename) -> std::wstring;

    [[nodiscard]]
    static std::wstring streamContentToWString(std::wistream *stream);
};

#endif