#include <iostream>
#include <string>

#include "Corpus.hpp"
#include "File.hpp"

namespace MOCK::FILE {
    static std::wstring mockFileContent;
}

auto File::fileContentToWString(std::string filename) -> std::wstring {
    return MOCK::FILE::mockFileContent;
}

int main() {
    MOCK::FILE::mockFileContent = L"";

    Corpus<std::string> c;

    c.addDocument("","");

    // if regress, expect SIGSEVC to return 139
    c.buildIndexNGram(3);

    return 0;
}