#include <iostream>
#include <string>

#include "Corpus.hpp"
#include "File.hpp"

namespace MOCK_FILE {
    static std::wstring mockContent;
}

auto File::fileContentToWString(std::string filename) -> std::wstring {
    return MOCK_FILE::mockContent;
}

int main() {
    MOCK_FILE::mockContent = L"";

    Corpus<std::string> c;

    c.addDocument("","");

    try {
        c.buildIndexNGram(3);
    } catch(...) {
        return 1;
    }

    return 0;
}