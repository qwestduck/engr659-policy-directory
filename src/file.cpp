#include <codecvt>
#include <locale>
#include <sstream>
#include <string>

#include "File.hpp"

auto File::fileContentToWString(const std::string &filename) -> std::wstring {
    auto f = std::wifstream{filename};
    f.imbue(std::locale(f.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    if(f) {
        std::wstringstream stream;
        stream << f.rdbuf();

        f.close();

        return stream.str();
    }

    return std::wstring{};
}