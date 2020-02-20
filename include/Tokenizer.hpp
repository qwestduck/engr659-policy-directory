#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

template <class T>
class Tokenizer {
    std::string id;
protected:
    Tokenizer(const std::string & id) : id(id) { }
public:
    std::string getId() const { return id; }
    virtual std::vector<T> tokenize(std::wstring) const = 0;
};

#endif