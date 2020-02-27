#include <sstream>
#include <string>

#include "File.hpp"

auto File::fileContentToWString(std::string filename) -> std::wstring {
    std::wifstream fin(filename);
    std::wstringstream buffer;
    buffer << fin.rdbuf();

    return buffer.str();
}