#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <sstream>
#include <string>

class File {
public:
    File() = default;

    [[nodiscard]]
    static auto fileContentToWString(std::string filename) -> std::wstring;
};

#endif