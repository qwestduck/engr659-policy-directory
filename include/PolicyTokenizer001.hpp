#ifndef POLICYTOKENIZER001_HPP
#define POLICYTOKENIZER001_HPP

#include "Tokenizer.hpp"

#include <algorithm>
#include <boost/algorithm/string.hpp>

template <class T>
class PolicyTokenizer001: public Tokenizer<T> {

public:
    PolicyTokenizer001() : Tokenizer<T>("PolicyTokenizer001") { }

    auto tokenize(std::wstring fulltext) const -> std::vector<T>;
};

template <>
class PolicyTokenizer001<std::wstring>: public Tokenizer<std::wstring> {
public:
    PolicyTokenizer001() : Tokenizer<std::wstring>("PolicyTokenizer001") { }

    auto tokenize(std::wstring fulltext) const -> std::vector<std::wstring> {
        std::vector<std::wstring> result;

        std::transform(fulltext.begin(), fulltext.end(), fulltext.begin(), ::tolower);
        fulltext.erase(std::remove(fulltext.begin(), fulltext.end(), '.'), fulltext.end());
        boost::split(result, fulltext, boost::is_any_of(L"\t\r\n \"“,()…_:"), boost::token_compress_on);

        return result;
    }
};

#endif