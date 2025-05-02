#ifndef INT_MOD_H
#define INT_MOD_H

#include <iostream>
#include <stdexcept>
#include "Logger.h"
using namespace std;

class IntMod {
private:
    long long val;
    long long p;
    static long long defaultMod;
    static bool defaultModSet;
    void abs();
    void norm();
    void check_base(const IntMod& b) const;

    // Power algorithms
    long long powerModL2R(long long e);
    long long powerModR2L(long long e);

public:
    // Constructors
    IntMod();
    IntMod(long long val);
    IntMod(long long val, long long p);

    // Assignment
    IntMod operator=(long long a);

    // Arithmetic operators
    IntMod operator+(const IntMod& b) const;
    IntMod operator+(long long b) const;
    IntMod operator-(const IntMod& b) const;
    IntMod operator-(long long b) const;
    IntMod operator*(const IntMod& b) const;
    IntMod operator*(long long b) const;
    IntMod operator/(const IntMod& b) const;
    IntMod pow(long long e);

    // Increment/Decrement
    IntMod operator++();
    IntMod operator++(int);
    IntMod operator--();
    IntMod operator--(int);

    // Compound assignment
    IntMod& operator+=(const IntMod& b);
    IntMod& operator+=(long long b);
    IntMod& operator-=(const IntMod& b);
    IntMod& operator-=(long long b);
    IntMod& operator*=(const IntMod& b);
    IntMod& operator*=(long long b);

    // Unary operators
    IntMod operator+() const;
    IntMod operator-() const;

    // Comparison operators
    bool operator==(const IntMod& b) const;
    bool operator==(int b) const;
    bool operator!=(const IntMod& b) const;
    bool operator!=(int b) const;
    bool operator<(const IntMod& b) const;
    bool operator<(int b) const;
    bool operator<=(const IntMod& b) const;
    bool operator<=(int b) const;
    bool operator>(const IntMod& b) const;
    bool operator>(int b) const;
    bool operator>=(const IntMod& b) const;
    bool operator>=(int b) const;

    // Casting
    operator short() const {
      return (short) this->val;
    }
    operator int() const {
      return (int) this->val;
    }
    operator long() const {
      return (long) this->val;
    }
    operator float() const {
      return (float) this->val;
    }
    operator double() const {
      return (double) this->val;
    }

    // Stream operators
    friend ostream& operator<<(ostream& os, const IntMod& a);
    friend istream& operator>>(istream& is, IntMod& a);
    string toString() const;

    /* ACCESSORS */
    long long modulus() const;
    static bool isDefaultModSet() {
      return defaultModSet;
    }
    static void setDefaultModulus(long long mod) {
      defaultMod = mod;
      IntMod::defaultModSet = true;
      Logger::log(MessageType::DEBUG, "Default Divisor", "Default devisor set to " + to_string(mod));
    }
    static long long getDefaultModulus() {
      if (!isDefaultModSet()) {
        throw runtime_error("Default modulus not set.");
      }
      return defaultMod;
    }
};

inline std::string to_string(const IntMod& a) {
  return a.toString();
}

#endif