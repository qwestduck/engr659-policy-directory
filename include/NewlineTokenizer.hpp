#ifndef NEWLINETOKENIZER_HPP
#define NEWLINETOKENIZER_HPP

#include "Tokenizer.hpp"

#include <boost/algorithm/string.hpp>

template <class T>
class NewlineTokenizer: public Tokenizer<T> {

public:
    NewlineTokenizer() : Tokenizer<T>("NewlineTokenizer") { }

    std::vector<T> tokenize(std::wstring fulltext) const;
};

template <>
class NewlineTokenizer<std::wstring>: public Tokenizer<std::wstring> {
public:
    NewlineTokenizer() : Tokenizer<std::wstring>("NewlineTokenizer") { }

    std::vector<std::wstring> tokenize(std::wstring fulltext) const {
        std::vector<std::wstring> result;
        boost::split(result, fulltext, boost::is_any_of(L"\r\n"), boost::token_compress_on);

        return result;
    }
};

#endif