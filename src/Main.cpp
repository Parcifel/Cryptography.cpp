#include <iostream>
using namespace std;

#include "Poly.h"
#include "IntMod.h"
#include "Logger.h"
#include "Helper.h"

int main() {
  Logger::log(MessageType::SUCCESS, "System", "Application started");

  // IntMod::setDefaultModulus(37);
  // IntMod a1 = IntMod(2);
  // int e1 = 19;
  // int e2 = 12;


  // Logger::log(MessageType::INFO, "", "g = " + a1.toString());
  // cout << "g = " << a1 << endl;
  // cout << "e1 = " << e1 << endl;
  // cout << "e2 = " << e2 << endl;
  // IntMod B = a1.pow(e1);
  // cout << "B = " << B << endl;
  // IntMod S = B.pow(12);
  // IntMod AB = a1.pow(e1*e2);
  // cout << "S = " << S << endl;
  // cout << "AB = " << AB << endl;

  // Logger::log(MessageType::DEBUG, "", IntMod(2, 3));

  // int d = euclidAlgo(4864, 3458);
  // Logger::log(MessageType::INFO, "Euclidean Algo", "gcd(4864, 3458) = " + to_string(d));
  // vector<int> D = extendedEuclidAlgo(29, 11);
  // vector<vector<int>> D_tab = {D};

  // Logger::table(MessageType::INFO, "Extended Euclidean Algo", {}, D_tab);

  // IntMod::setDefaultModulus(4);
  // IntMod a(5);
  // short b = a;
  // int c = a;
  // long d = a;
  // float e = a;
  // double f = a;
  
  // Logger::log(MessageType::INFO, "IntMod", a);
  // Logger::log(MessageType::INFO, "short", b);
  // Logger::log(MessageType::INFO, "int", c);
  // Logger::log(MessageType::INFO, "long", d);
  // Logger::log(MessageType::INFO, "float", e);
  // Logger::log(MessageType::INFO, "double", f);

  int p = 997;
  Logger::log(MessageType::INFO, "Prime", isPrime(p));


  vector<int> primes = {
    100003,  // prime
    999983,  // prime (largest 6-digit prime)
    104729,  // prime
    104743   // prime
  };

  // Test composite numbers
  vector<int> composites = {
    100001,  // 73 × 1,370
    123456,  // 2^6 × 3 × 643
    999966,  // 2 × 3 × 166,661
    104730   // 2 × 3 × 17,455
  };

  Logger::log(MessageType::INFO, "Prime Tests", "Testing large numbers for primality");
  Logger::blank();

  for (int n : primes) {
    Logger::log(MessageType::INFO, "Testing " + to_string(n), isPrime(n));
  }

  Logger::blank();

  for (int n : composites) {
    Logger::log(MessageType::INFO, "Testing " + to_string(n), isPrime(n));
  }
 
  Logger::log(MessageType::SUCCESS, "System", "Application finished");
  return 0;
}