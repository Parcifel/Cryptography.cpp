#ifndef INT_MOD_H
#define INT_MOD_H

#include <iostream>
#include <stdexcept>
#include "Logger.h"
using namespace std;

class IntMod {
private:
    long long val;
    int p;
    static int defaultMod;
    static bool defaultModSet;
    void abs();
    void norm();
    void check_base(const IntMod& b) const;

    // Power algorithms
    int powerModL2R(int e);
    int powerModR2L(int e);

public:
    // Constructors
    IntMod(int val);
    IntMod(int val, int p);

    // Assignment
    IntMod operator=(int a);

    // Arithmetic operators
    IntMod operator+(const IntMod& b) const;
    IntMod operator+(int b) const;
    IntMod operator-(const IntMod& b) const;
    IntMod operator-(int b) const;
    IntMod operator*(const IntMod& b) const;
    IntMod operator*(int b) const;
    IntMod operator/(const IntMod& b) const;
    IntMod pow(int e);

    // Increment/Decrement
    IntMod operator++();
    IntMod operator++(int);
    IntMod operator--();
    IntMod operator--(int);

    // Compound assignment
    IntMod& operator+=(const IntMod& b);
    IntMod& operator+=(int b);
    IntMod& operator-=(const IntMod& b);
    IntMod& operator-=(int b);
    IntMod& operator*=(const IntMod& b);
    IntMod& operator*=(int b);

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
    int modulus() const;
    static bool isDefaultModSet() {
      return defaultModSet;
    }
    static void setDefaultModulus(int mod) {
      defaultMod = mod;
      IntMod::defaultModSet = true;
      Logger::log(MessageType::DEBUG, "Default Divisor", "Default devisor set to " + to_string(mod));
    }
    static int getDefaultModulus() {
      if (!isDefaultModSet()) {
        throw runtime_error("Default modulus not set.");
      }
      return defaultMod;
    }
};

inline std::string to_string(const IntMod& a) {
  return a.toString();
}

#endif // INT_MOD_H