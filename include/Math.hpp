#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <stdexcept>
#include <vector>

class Math {
public:
    Math() = default;

    [[nodiscard]]
    static auto _divide(int num, int den) -> double {
        return divide(static_cast<double>(num), static_cast<double>(den));
    }

    [[nodiscard]]
    static auto divide(double num, double den) -> double {
        if (den == 0.0) {
            throw std::overflow_error("Division by zero");
        }

        return (num / den);
    }

    [[nodiscard]]
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

    [[nodiscard]]
    static auto hadamardProduct(std::vector<double> a, std::vector<double> b) -> std::vector<double> {
        std::vector<double> ret = a;

        if(a.size() != b.size()) {
            throw std::overflow_error("Vector size mismatch");
        }

        for(int i = 0; i < a.size(); i++) {
            ret[i] = a[i] * b[i];
        }

        return ret;
    }

    [[nodiscard]]
    static auto vectorAdd(const std::vector<double> & a, const std::vector<double> & b) -> std::vector<double> {
        std::vector<double> ret = a;

        if(a.size() != b.size()) {
            throw std::overflow_error("Vector size mismatch");
        }

        for(int i = 0; i < a.size(); i++) {
            ret[i] += b[i];
        }

        return ret;
    }

    [[nodiscard]]
    static auto scalarProduct(const std::vector<double> & a, double b) -> std::vector<double> {
        std::vector<double> ret = a;

        for(auto & el: ret) {
            el *= b;
        }

        return ret;
    }

    template<class T>
    [[nodiscard]]
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

    template<class T>
    [[nodiscard]]
    static auto linearNormalize(std::vector<T> a, T min, T max, bool invert) -> std::vector<T> {
        T factor = max - min;

        for(auto & el : a) {
            if(factor == 0) {
                el = 0;
            } else {
                el = el / (max - min);
            }

            if(invert) {
                el = 1.0 - el;
            }
        }

        return a;
    }
};

#endif