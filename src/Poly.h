#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "IntMod.h"

template <typename T> struct ring_traits {
    static T zero() {
        return T(0);
    }
};

template <typename T>
class Poly {
private:
    std::vector<T> coeffs;
    void reduce();

public:
    // Constructors
    Poly();
    Poly(const std::vector<T>& coef);
    Poly(int deg, const T* coef);
    Poly(const Poly& a) = default;

    // Assignment
    Poly& operator=(const Poly& a) = default;

    // Access
    T& operator[](int deg);
    const T operator[](int deg) const;

    // Arithmetic
    Poly operator+(const Poly& b) const;
    Poly operator-(const Poly& b) const;
    Poly operator*(const Poly& b) const;
    
    // Evaluation
    T evaluate(const T& x) const;

    // Getters
    int degree() const;

    // Stream operator
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Poly<U>& p);
};

#include "Poly.tpp"  // Template implementation file

#endif