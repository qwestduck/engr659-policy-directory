#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <sstream>
#include <string>

class File {
public:
    File() { }

    static std::wstring fileContentToWString(std::string filename) {
        std::wifstream fin(filename);
        std::wstringstream buffer;
        buffer << fin.rdbuf();

        return buffer.str();
    }
};

#endif