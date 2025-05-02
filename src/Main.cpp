#include <iostream>
using namespace std;

#include "Poly.h"
#include "IntMod.h"
#include "Logger.h"
#include "Helper.h"
#include "RSAEnc.h"

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


void test_modular_arithmetic();
void test_casting();
void test_euclidean_algorithms();
void test_primality();
void test_division();
void test_prime_factorization();
void test_euler_phi();
void test_random_prime_generation();
void test_fg_function();
void test_fg(int p);
void test_rsa_key_generation();


int main() {
  init();


  // IntMod::setDefaultModulus(946720);
  // IntMod e(690403, 946720);
  // IntMod d(88133, 946720);
  // Logger::log(MessageType::INFO, "e", e); 
  // Logger::log(MessageType::INFO, "d", d); 
  // Logger::log(MessageType::INFO, "ed", e*d); 

  // extendedEuclidAlgo(946720, 690403);

  int p = 241, q = 149;

  Logger::log(MessageType::INFO, "Random Prime", p);
  Logger::log(MessageType::INFO, "Prime bits", decToBin(p));
  Logger::log(MessageType::INFO, "Random Prime", q);
  Logger::log(MessageType::INFO, "Prime bits", decToBin(q));
  
  RSAEnc rsa(p, q, 30349);
  Logger::log(MessageType::INFO, "n bits", decToBin(35909));
  Logger::log(MessageType::INFO, "e bits", decToBin(30349));
  Logger::log(MessageType::INFO, "d bits", decToBin(5509));
  
  vector<bool> encrypted_msg = rsa.encrypt("MEET AT NINE");
  string decrypted_msg = rsa.decrypt(encrypted_msg);

  close();
  return 0;
}


void test_modular_arithmetic() {
  Logger::log(MessageType::INFO, "Test", "Modular Arithmetic Operators");
  IntMod::setDefaultModulus(7);
  IntMod a(3), b(2);
  Logger::log(MessageType::INFO, "a", a);
  Logger::log(MessageType::INFO, "b", b);
  Logger::log(MessageType::INFO, "a + b", a + b);
  Logger::log(MessageType::INFO, "a - b", a - b);
  Logger::log(MessageType::INFO, "a * b", a * b);
  Logger::log(MessageType::INFO, "a / b", a / b);
}

void test_casting() {
  Logger::log(MessageType::INFO, "Test", "IntMod Casting");
  IntMod::setDefaultModulus(4);
  IntMod a(5);
  short b = a;
  int c = a;
  long d = a;
  float e = a;
  double f = a;
  Logger::log(MessageType::INFO, "IntMod", a);
  Logger::log(MessageType::INFO, "short", b);
  Logger::log(MessageType::INFO, "int", c);
  Logger::log(MessageType::INFO, "long", d);
  Logger::log(MessageType::INFO, "float", e);
  Logger::log(MessageType::INFO, "double", f);
}

void test_euclidean_algorithms() {
  Logger::log(MessageType::INFO, "Test", "Euclidean Algorithms");
  int d = euclidAlgo(4864, 3458);
  Logger::log(MessageType::INFO, "Euclidean Algo", "gcd(4864, 3458) = " + to_string(d));
  vector<long long> D = extendedEuclidAlgo(29, 11);
  vector<vector<long long>> D_tab = {D};
  Logger::table(MessageType::INFO, "Extended Euclidean Algo", {}, D_tab);
}

void test_primality() {
  Logger::log(MessageType::INFO, "Test", "Primality Testing");
  vector<int> primes = {100003, 999983, 104729, 104743};
  vector<int> composites = {100001, 123456, 999966, 104730};
  for (int n : primes) {
      Logger::log(MessageType::INFO, "Testing " + to_string(n), isPrime(n));
  }
  for (int n : composites) {
      Logger::log(MessageType::INFO, "Testing " + to_string(n), isPrime(n));
  }
}

void test_division() {
  Logger::log(MessageType::INFO, "Division Tests", "Testing division in Z/pZ");
  Logger::blank(MessageType::DEBUG);
  try {
      IntMod::setDefaultModulus(7);
      IntMod a(3), b(2);
      IntMod c = a / b;
      Logger::log(MessageType::INFO, "3/2 mod 7", c);
      IntMod d = a / IntMod(1);
      Logger::log(MessageType::INFO, "3/1 mod 7", d);
      IntMod e(6), f(3);
      IntMod g = e / f;
      Logger::log(MessageType::INFO, "6/3 mod 7", g);
  } catch (const exception& e) {
      Logger::log(MessageType::DEBUG, "Error", e.what());
  }
  Logger::blank(MessageType::DEBUG);
}

void test_prime_factorization() {
  int PRIME_16 = 65521;
  Logger::log(MessageType::INFO, "Large Prime", PRIME_16);
  vector<vector<int>> primeFactors = primeFactorization(PRIME_16-1);
  Logger::table(MessageType::DEBUG, "Prime Factors", {"Factors", "e"}, primeFactors);
}

void test_euler_phi() {
  int PRIME_8 = 251;
  int PRIME_10 = 1019;
  int PRIME_16 = 65521;
  int PRIME_32 = 2147483647;
  Logger::log(MessageType::INFO, "Euler phi", to_string(PRIME_10) + " " + to_string(eulerPhi(PRIME_10)));
  Logger::log(MessageType::INFO, "Euler phi", to_string(PRIME_16) + " " + to_string(eulerPhi(PRIME_16)));
  Logger::log(MessageType::INFO, "Euler phi", to_string(PRIME_32) + " " + to_string(eulerPhi(PRIME_32)));
  Logger::log(MessageType::INFO, "Euler phi", to_string(PRIME_8) + " " + to_string(eulerPhi(PRIME_8)));
}

void test_random_prime_generation() {
  Logger::log(MessageType::INFO, "Random Prime 10", generatePrime(10));
  Logger::log(MessageType::INFO, "Random Prime 12", generatePrime(12));
  Logger::log(MessageType::INFO, "Random Prime 16", generatePrime(16));
  Logger::log(MessageType::INFO, "Random Prime 20", generatePrime(20));
}

void test_fg_function() {
  int PRIME_8 = 251;
  int PRIME_10 = 1019;
  int PRIME_16 = 65521;
  test_fg(743);
  test_fg(PRIME_10);
  test_fg(PRIME_16);
  test_fg(PRIME_8);
}

void test_fg(int p) {
  int g = findGenerator(p);
  Logger::log(MessageType::INFO, "Generator", g);
  Logger::blank(MessageType::INFO);

  IntMod::setDefaultModulus(p);
  IntMod a(g);
  Logger::log(MessageType::INFO, "IntMod element", a);

  size_t anomily = 0;
  for (long i = 2; i < p-1; i++) {
    if (a.pow(i) == 1) {
      anomily += 1;
      Logger::log(MessageType::INFO, "Power to 1", i);
    }
  }

  Logger::log(MessageType::INFO, "Last Exponent", a.pow(p-1));
}

void test_rsa_key_generation() {
  Logger::log(MessageType::INFO, "Test", "RSA Key Generation");
  try {
      RSAEnc rsa(1019, 65521); // Example with two primes
  } catch (const std::exception& e) {
      Logger::log(MessageType::ERROR, "RSAEnc", e.what());
  }
}