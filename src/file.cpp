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

auto File::streamContentToWString(std::wistream *stream_in) -> std::wstring {
    if(stream_in) {
        stream_in->imbue(std::locale(stream_in->getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

        std::wstringstream stream_out;
        stream_out << stream_in->rdbuf();

        return stream_out.str();
    }

    return std::wstring{};
}