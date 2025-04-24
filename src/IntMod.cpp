#include "IntMod.h"
#include "Helper.h"
#include <iostream>
#include <bitset>
using namespace std;

int IntMod::defaultMod = 2;
bool IntMod::defaultModSet = false;

void IntMod::abs() {
  while (this->val < 0) {
    this->val += p;
  }
}

void IntMod::norm() {
  abs();
  this->val = this->val % this->p;
}

void IntMod::check_base(const IntMod& b) const{
  if (this->p != b.p) {
    throw invalid_argument("Moduli must be equal. Expected " + to_string(this->p) + "; got " + to_string(b.p));
  }
}

int IntMod::powerModL2R(int e) {
  if (e < 0) {
    throw invalid_argument("Expected non-negative exponent, got" + to_string(e));
  }

  bitset<32> bits = e;
  long long r = 1;
  long long b = val;
  bool start = false;

  // == for debugging output ==
  vector<vector<string>> table = {{"", "", to_string(r)}};
  // == ==

  for (int i = 31; i >= 0; i--) {
    r = (r * r) % p;
    // if the bit is a 1
    if (bits[i]) {
      start = true; // leading bit has been found
      r = (r * b) % p;
    }

  // == for debugging output ==
    if (start) {
      if (bits[i]) {
        table.push_back({to_string(i), "1", to_string(r)});
      } else {
        table.push_back({to_string(i), "0", to_string(r)});
      }
    }
  }
  Logger::blank(MessageType::DEBUG, 2);
  Logger::table(
    MessageType::VERBOSE, 
    "Modulo Power (L2R)", 
    {"i", "e[i]", "r"}, 
    table
  );
  Logger::log(
    MessageType::DEBUG, 
    "Modulo Power (L2R)", 
    to_string(val) + "^" + to_string(e) + " = " + to_string(r)
  );
  Logger::blank(MessageType::DEBUG);
  // == == 
  
  return (int) r;
}

int IntMod::powerModR2L(int exp) {
  if (exp < 0) {
    throw invalid_argument("Expected non-negative exponent, got" + to_string(exp));
  }

  long long e = exp;
  long long r = 1;
  long long b = val;

  // == for debug output ==
  vector<vector<long long>> table = {{r, b, e}};
  // == ==

  while (e > 0) {
    // if e is odd
    if ((e % 2) == 1) {
      r = (r * b) % p;
    }
    b = (b * b) % p;
    e = e / 2;
    table.push_back({r, b, e});
  }

  // == ==
  Logger::blank(MessageType::DEBUG, 2);
  Logger::table(
    MessageType::VERBOSE,
    "Modulo Power (R2L)",
    {"r", "b", "e"},
    table
  );
  Logger::log(
    MessageType::DEBUG, 
    "Modulo Power (R2L)", 
    to_string(val) + "^" + to_string(exp) + " = " + to_string(r)
  );
  Logger::blank(MessageType::DEBUG);
  //== ==

  return (int) r;
}

IntMod::IntMod(int val) {
  if (!isDefaultModSet()) {
    throw runtime_error("Default modulus not set.");
  }
  this->val = val;
  this->p = defaultMod;
  norm();
}

IntMod::IntMod(int val, int p) {
  this->val = val;
  this->p = p;
  norm();
  IntMod::setDefaultModulus(p);
}

/* ASSIGNMENT */
IntMod IntMod::operator=(int a) {
  this->val = a % p;
  norm();
  return *this;
}

/*  ADDITION */
IntMod IntMod::operator+(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  IntMod result(val);
  result = (this->val + b.val) % p;
  return result;
}

IntMod IntMod::operator+(int b) const {
  IntMod result(val);
  result = (this->val + b) % p;
  return result;
}

/* SUBTRACTION */
IntMod IntMod::operator-(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  IntMod result(val);
  result = (this->val - b.val) % p;
  return result;
}

IntMod IntMod::operator-(int b) const {
  IntMod result(val);
  result = (this->val - b) % p;
  return result;
}

/* MULTIPLICATION */
IntMod IntMod::operator*(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  IntMod result(val);
  result = (this->val * b.val) % p;
  return result;
}

IntMod IntMod::operator*(int b) const {
  IntMod result(val);
  result = (this->val * b) % p;
  return result;
}

/* DIVISION */
IntMod IntMod::operator/(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  // p must be prime to fint the modular inverse
  if (!isPrime(p)) {
    throw invalid_argument("Cannor find modular inverse of non prime divisor " + to_string(p));
  }

  // use extended euclidean algorithm to find modular inverse of b
  vector<int> eea = extendedEuclidAlgo((int)p, (int)b.val);
  IntMod inv(eea[2], p);

  IntMod result(val);
  result = result * inv;

  return result;
}

/* POWER */
IntMod IntMod::pow(int e) {
  if (e < 0) {
    // get inverse and then take exponenet of that
    IntMod result = 1 / e;
    return result.pow(e*-1);
  }
  if (e == 1) {
    return IntMod(1, p);
  }

  IntMod::setDefaultModulus(p);
  int a = powerModL2R(e);
  IntMod l2r(a);
  // int b = powerModR2L(e);
  // IntMod r2l(b);

  // if (l2r != r2l) {
  //   throw invalid_argument("Arithmatic exception. Power functions didnt get the smae result, l2r got " + l2r.toString() + " but r2l got " + r2l.toString());
  // }

  return l2r;
}

/* MODULO */
// This operatino does not exist for this DataType

/* INCREMENT */
IntMod IntMod::operator++() {
  this->val = (this->val + 1) % p;
  norm();
  return *this;
}

IntMod IntMod::operator++(int) {
  IntMod temp = *this;
  ++(*this);
  return temp;
}

/* DECREMENT */
IntMod IntMod::operator--() {
  this->val = (this->val - 1) % p;
  norm();
  return *this;
}

IntMod IntMod::operator--(int) {
  IntMod temp = *this;
  --(*this);
  return temp;
}

/* COMPOUND OPERATORS */
IntMod& IntMod::operator+=(const IntMod& b) {
  // assert(this->p == b.p);
  check_base(b);
  this->val = (this->val + b.val) % p;
  norm();
  return *this;
}

IntMod& IntMod::operator+=(int b) {
  this->val = (this->val + b) % p;
  norm();
  return *this;
}

IntMod& IntMod::operator-=(const IntMod& b) {
  // assert(this->p == b.p);
  check_base(b);
  this->val = (this->val - b.val) % p;
  norm();
  return *this;
}

IntMod& IntMod::operator-=(int b) {
  this->val = (this->val - b) % p;
  norm();
  return *this;
}

IntMod& IntMod::operator*=(const IntMod& b) {
  // assert(this->p == b.p);
  check_base(b);
  this->val = (this->val * b.val) % p;
  norm();
  return *this;
}

IntMod& IntMod::operator*=(int b) {
  this->val = (this->val * b) % p;
  norm();
  return *this;
}

// Compound division is going to require an imlementation of devision

/* UNARY */
IntMod IntMod::operator+() const {
  return *this;
}

IntMod IntMod::operator-() const {
  IntMod result(val);
  result.val = (-val) % p;
  return result;
}

/* BOOLEAN */
bool IntMod::operator==(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val == b.val;
}
bool IntMod::operator==(int b) const {
  b = b % p;
  return this->val == b;
}

bool IntMod::operator!=(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val != b.val;
}
bool IntMod::operator!=(int b) const {
  b = b % p;
  return this->val != b;
}

bool IntMod::operator<(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val < b.val;
}
bool IntMod::operator<(int b) const {
  b = b % p;
  return this->val < b;
}

bool IntMod::operator<=(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val <= b.val;
}
bool IntMod::operator<=(int b) const {
  b = b % p;
  return this->val <= b;
}

bool IntMod::operator>(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val > b.val;
}
bool IntMod::operator>(int b) const {
  b = b % p;
  return this->val > b;
}

bool IntMod::operator>=(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val >= b.val;
}
bool IntMod::operator>=(int b) const {
  b = b % p;
  return this->val >= b;
}

/* ADMIN */
ostream& operator<<(ostream& os, const IntMod& a) {
  os << a.val << " (mod " << a.p << ")";
  return os;
}

istream& operator>>(istream& is, IntMod& a) {
  int val;
  is >> val;
  a = val;
  return is;
}

string IntMod::toString() const {
  return to_string(val) + " (mod " + to_string(p) + ")";
}

/* ACCESSORS */
int IntMod::modulus() const {
  return p;
}

   
// /* TESTING */
// int main() {
//   IntMod a(10), b(8);
//   a = 12;
//   b = 12;
//   a = a - b;
//   a.print();

//   return 0;
// }
