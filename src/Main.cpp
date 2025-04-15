#include <iostream>
using namespace std;

#include "Poly.h"
#include "IntMod.h"
#include "Logger.h"
#include "Helper.h"

void init() {
  #ifdef DEBUG_MODE
    Logger::enableDebug();
  #endif

  #ifdef VERBOSE_MODE
    Logger::enableVerbose();
  #endif

  Logger::log(MessageType::SUCCESS, "System", "Starting application");
  Logger::log(MessageType::DEBUG, "Debug", "Debug mode active");
  Logger::log(MessageType::VERBOSE, "Verbose", "Verbose mode active");
  Logger::blank(MessageType::INFO);
}

void close() {
  Logger::log(MessageType::SUCCESS, "System", "Application finished");
}

int main() {
  init();

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

  // int p = 997;
  // Logger::log(MessageType::INFO, "Prime", isPrime(p));


  // vector<int> primes = {
  //   100003,  // prime
  //   999983,  // prime (largest 6-digit prime)
  //   104729,  // prime
  //   104743   // prime
  // };

  // // Test composite numbers
  // vector<int> composites = {
  //   100001,  // 73 × 1,370
  //   123456,  // 2^6 × 3 × 643
  //   999966,  // 2 × 3 × 166,661
  //   104730   // 2 × 3 × 17,455
  // };

  // Logger::log(MessageType::INFO, "Prime Tests", "Testing large numbers for primality");
  // // Logger::blank();

  // for (int n : primes) {
  //   Logger::log(MessageType::INFO, "Testing " + to_string(n), isPrime(n));
  // }

  // // Logger::blank();

  // for (int n : composites) {
  //   Logger::log(MessageType::INFO, "Testing " + to_string(n), isPrime(n));
  // }

  Logger::log(MessageType::INFO, "Division Tests", "Testing division in Z/pZ");
  Logger::blank(MessageType::DEBUG);

  try {
    // Test in Z/7Z
    IntMod::setDefaultModulus(7);
    IntMod a(3);
    IntMod b(2);
    IntMod c = a / b;  // Should be 5 because 2 * 5 ≡ 3 (mod 7)
    Logger::log(MessageType::INFO, "3/2 mod 7", c);

    // Test division by 1
    IntMod d = a / IntMod(1);  // Should be 3
    Logger::log(MessageType::INFO, "3/1 mod 7", d);

    // Test division where result > modulus
    IntMod e(6);
    IntMod f(3);
    IntMod g = e / f;  // Should be 2 because 3 * 2 ≡ 6 (mod 7)
    Logger::log(MessageType::INFO, "6/3 mod 7", g);

  } catch (const exception& e) {
    Logger::log(MessageType::DEBUG, "Error", e.what());
  }

  Logger::blank(MessageType::DEBUG);
 
  close();
  return 0;
}