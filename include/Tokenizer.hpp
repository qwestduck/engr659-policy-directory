#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

template <class T>
class Tokenizer {

public:
    Tokenizer() { }
    virtual std::vector<T> tokenize(std::wstring) const = 0;
};

#endif