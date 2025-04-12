#include "IntMod.h"
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
  int r = 1;
  int b = val;
  bool start = false;

  // == for debugging output ==
  vector<string> headers = {"i", "e[i]", "r"};
  vector<vector<string>> data = {{"", "", to_string(r)}};
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
        data.push_back({to_string(i), "1", to_string(r)});
      } else {
        data.push_back({to_string(i), "0", to_string(r)});
      }
    }
  }
  Logger::table(MessageType::DEBUG, "Modulo Power (L2R)", headers, data);
  // == == 
  
  return r;
}

int IntMod::powerModR2L(int e) {
  if (e < 0) {
    throw invalid_argument("Expected non-negative exponent, got" + to_string(e));
  }

  int r = 1;
  int b = val;

  while (e > 0) {
    // if e is odd
    if ((e % 2) == 1) {
      r = (r * b) % p;
    }
    b = (b * b) % p;
    e = e / 2;
  }

  return r;
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
  IntMod result(p);
  result = (this->val + b.val) % p;
  return result;
}

IntMod IntMod::operator+(int b) const {
  IntMod result(p);
  result = (this->val + b) % p;
  return result;
}

/* SUBTRACTION */
IntMod IntMod::operator-(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  IntMod result(p);
  result = (this->val - b.val) % p;
  return result;
}

IntMod IntMod::operator-(int b) const {
  IntMod result(p);
  result = (this->val - b) % p;
  return result;
}

/* MULTIPLICATION */
IntMod IntMod::operator*(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  IntMod result(p);
  result = (this->val * b.val) % p;
  return result;
}

IntMod IntMod::operator*(int b) const {
  IntMod result(p);
  result = (this->val * b) % p;
  return result;
}

/* DIVISION */
IntMod IntMod::operator/(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  // Only works if p is a prime
  // Implement requires finding the multiplicative inverse
  return *this;
}

/* POWER */
IntMod IntMod::pow(int e) {
  if (e < 0) {
    // get inverse and then take exponenet of that
    return IntMod(0);
  }

  int l2r = powerModL2R(e);
  int r2l = powerModR2L(e);

  if (l2r != r2l) {
    throw invalid_argument("Arithmatic exception. Power functions didnt get the smae result, l2r got " + to_string(l2r) + " but r2l got " + to_string(r2l));
  }

  IntMod result(l2r);
  return result;
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
  IntMod result(p);
  result.val = (-val) % p;
  return result;
}

/* BOOLEAN */
bool IntMod::operator==(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val == b.val;
}

bool IntMod::operator!=(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val != b.val;
}

bool IntMod::operator<(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val < b.val;
}

bool IntMod::operator<=(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val <= b.val;
}

bool IntMod::operator>(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val > b.val;
}

bool IntMod::operator>=(const IntMod& b) const {
  // assert(this->p == b.p);
  check_base(b);
  return this->val >= b.val;
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

string IntMod::toString() {
  stringstream ss;
  ss << this->val << " (mod " << this->p << ")";
  return ss.str();
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
