#include <string>

#include "Corpus.hpp"
#include "File.hpp"

namespace MOCK::FILE {
    static std::wstring mockFileContent;
} // namespace MOCK::FILE

auto File::fileContentToWString(const std::string&  /*filename*/) -> std::wstring {
    return MOCK::FILE::mockFileContent;
}

auto main() -> int {
    MOCK::FILE::mockFileContent = L"";

    Corpus<std::string> c;

    c.addDocument("","");

    // if regress, expect SIGSEVC to return 139
    c.buildIndexNGram(3);

    return 0;
}