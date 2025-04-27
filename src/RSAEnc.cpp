#include "RSAEnc.h"
#include "Helper.h"
#include "IntMod.h"

RSAEnc::RSAEnc() : p(0), q(0), n(0), phi(0) {
  // Default constructor
  Logger::log(MessageType::ERROR, "RSAEnc", "Default constructor called");
}

RSAEnc::RSAEnc(long long p, long long q) : p(p), q(q) {
  Logger::log(MessageType::INFO, "RSAEnc", "RSA initializing ...");

  if (p <= 1 || q <= 1) {
    throw invalid_argument("p and q must be greater than 1");
  }
  if (!isPrime(p) || !isPrime(q)) {
    throw invalid_argument("p and q must be prime numbers");
  }
  Logger::log(MessageType::INFO, "p", to_string(p));
  Logger::log(MessageType::INFO, "q", to_string(q));

  n = p * q;
  phi = (p - 1) * (q - 1);
  Logger::log(MessageType::INFO, "n", to_string(n));
  Logger::log(MessageType::INFO, "phi", to_string(phi));

  // Choose e such that 1 < e < phi and gcd(e, phi) = 1
  long long e_val = generateEncExp(phi);
  if (e_val <= 1 || e_val >= phi) {
    throw invalid_argument("e must be in the range (1, phi)");
  }
  if (euclidAlgo(e_val, phi) != 1) {
    throw invalid_argument("e must be coprime to phi");
  }

  // Calculate d, the modular multiplicative inverse of e mod phi
  long long d_val = extendedEuclidAlgo(e_val, phi)[2];

  e = IntMod(e_val, phi);
  d = IntMod(d_val, phi);

  Logger::log(MessageType::INFO, "e", to_string(e));
  Logger::log(MessageType::INFO, "d", to_string(d));
  Logger::log(MessageType::INFO, "RSAEnc", "RSA parameters initialized");
}