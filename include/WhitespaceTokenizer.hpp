#ifndef WHITESPACETOKENIZER_HPP
#define WHITESPACETOKENIZER_HPP

#include "Tokenizer.hpp"

#include <boost/algorithm/string.hpp> 

template <class T>
class WhitespaceTokenizer: public Tokenizer<T> {

public:
    WhitespaceTokenizer() : Tokenizer<T>("WhitespaceTokenizer") { }

    std::vector<T> tokenize(std::wstring fulltext) const;
};

template <>
class WhitespaceTokenizer<std::wstring>: public Tokenizer<std::wstring> {
public:
    WhitespaceTokenizer() : Tokenizer<std::wstring>("WhitespaceTokenizer") { }

    std::vector<std::wstring> tokenize(std::wstring fulltext) const {
        std::vector<std::wstring> result; 
        boost::split(result, fulltext, boost::is_any_of(L"\t\r\n \"“,()…_:"), boost::token_compress_on); 

        return result;
    }
};

#endif