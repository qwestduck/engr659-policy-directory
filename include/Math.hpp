#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <stdexcept>
#include <vector>

class Math {
public:
    Math() { }

    static double _divide(int num, int den) {
        return divide(static_cast<double>(num), static_cast<double>(den));
    }

    static double divide(double num, double den)
    {
        if (den == 0.0) {
            throw std::overflow_error("Division by zero");
        }

        return (num / den);
    }

    static double dotProduct(std::vector<double> a, std::vector<double> b) {
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
    static std::vector<T> euclideanNormalize(std::vector<T> a) {
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