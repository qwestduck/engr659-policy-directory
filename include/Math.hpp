#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <stdexcept>
#include <vector>

class Math {
public:
    Math() { }

    static auto _divide(int num, int den) -> double {
        return divide(static_cast<double>(num), static_cast<double>(den));
    }

    static auto divide(double num, double den) -> double {
        if (den == 0.0) {
            throw std::overflow_error("Division by zero");
        }

        return (num / den);
    }

    static auto dotProduct(std::vector<double> a, std::vector<double> b) -> double {
        double ret = 0;

        if(a.size() != b.size()) {
            throw std::overflow_error("Vector size mismatch");
        }

        for(int i = 0; i < a.size(); i++) {
            ret += a[i] * b[i];
        }

        return ret;
    }

    template<class T>
    static auto euclideanNormalize(std::vector<T> a) -> std::vector<T> {
        double divisor = 0;
        std::vector<T> ret = a;

        for(const auto & el : a) {
            divisor += el * el;
        }

        divisor = std::sqrt(divisor);

        for(int i = 0; i < a.size(); i++) {
            ret[i] = divide(a[i], divisor);
        }

        return ret;
    }
};

#endif