#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <utility>
#include <vector>

template <class T>
class Tokenizer {
    std::string id;
protected:
    explicit Tokenizer(std::string id) : id(std::move(id)) { }
public:
    [[nodiscard]]
    auto getId() const -> std::string { return id; }

    [[nodiscard]]
    virtual auto tokenize(std::wstring) const -> std::vector<T> = 0;
};

#endif