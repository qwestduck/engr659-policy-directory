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
    auto getId() const -> std::string { return id; }
    virtual auto tokenize(std::wstring) const -> std::vector<T> = 0;
};

#endif