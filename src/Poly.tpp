#ifndef POLY_TPP
#define POLY_TPP

#include <algorithm>
#include <iostream>
#include "Poly.h"

template <typename T>
Poly<T>::Poly() : coeffs{ring_traits<T>::zero()} {}

template <typename T>
Poly<T>::Poly(const vector<T>& coef) : coeffs(coef) {
  if (coeffs.empty()) {
    coeffs.push_back(ring_traits<T>::zero());
  }
  reduce();
}

template <typename T>
Poly<T>::Poly(int deg, const T* coef) {
  if (deg < 0) {
    throw invalid_argument("Degree must be an positive integer, got " + to_string(deg));
  }
  coeffs.assign(coef, coef + deg + 1);
  reduce();
}

/* ACCESS */
template <typename T>
T& Poly<T>::operator[](int deg) {
  if (deg >= coeffs.size()) {
    coeffs.resize(deg + 1, ring_traits<T>::zero());
  }
  return coeffs[deg];
}

template <typename T>
const T Poly<T>::operator[](int deg) const {
  if (deg >= coeffs.size()) {
    // return zero;
    return ring_traits<T>::zero();
  }
  return coeffs[deg];
}

/* ARITHMATIC */
template <typename T>
Poly<T> Poly<T>::operator+(const Poly& b) const {
  Poly result(*this);
  result.coeffs.resize(max(coeffs.size(), b.coeffs.size()), ring_traits<T>::zero());
  for (size_t i = 0; i < b.coeffs.size(); ++i) {
    result.coeffs[i] += b.coeffs[i];
  }
  result.reduce();
  return result;
}

template <typename T>
Poly<T> Poly<T>::operator-(const Poly& b) const {
  Poly result(*this);
  result.coeffs.resize(max(coeffs.size(), b.coeffs.size()), ring_traits<T>::zero());
  for (size_t i = 0; i < b.coeffs.size(); ++i) {
    result.coeffs[i] -= b.coeffs[i];
  }
  result.reduce();
  return result;
}

template <typename T>
Poly<T> Poly<T>::operator*(const Poly& b) const {
  vector<T> result(degree() + b.degree() + 1, ring_traits<T>::zero());
  for (size_t i = 0; i < coeffs.size(); ++i) {
    for (size_t j = 0; j < b.coeffs.size(); ++j) {
      result[i + j] += coeffs[i] * b.coeffs[j];
    }
  }
  return Poly(result);
}

template <typename T>
T Poly<T>::evaluate(const T& x) const {
  T result = ring_traits<T>::zero();
  T power = T(1);
  for (const T& c : coeffs) {
    result += c * power;
    power *= x;
  }
  return result;
}

/* GETTER */
template <typename T>
int Poly<T>::degree() const {
  return coeffs.size() - 1;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Poly<T>& p) {
  bool first = true;
  for (int i = p.degree(); i >= 0; --i) {
    if (p[i] == ring_traits<T>::zero()) continue;
    if (!first && p[i] > ring_traits<T>::zero()) os << " + ";
    if (p[i] != T(1) || i == 0) os << p[i];
    if (i > 0) os << "x";
    if (i > 1) os << "^" << i;
    first = false;
  }
  if (first) os << "0";
  return os;
}

#endif