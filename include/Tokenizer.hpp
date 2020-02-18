#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

template <class T>
class Tokenizer {
protected:
    std::string id;
public:
    Tokenizer() { }
    std::string getId() const { return id; }
    virtual std::vector<T> tokenize(std::wstring) const = 0;
};

#endif