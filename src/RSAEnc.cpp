#include <vector>
#include <bitset>
#include <string>
#include "RSAEnc.h"
#include "Helper.h"
#include "IntMod.h"

using namespace std;

void RSAEnc::setPrimeBitLength() {
  // Set the bit length of the primes p and q
  k = 0;
  long long l = n;
  while (l) {
    l >>= 1;
    ++k;
  }
}

vector<int> RSAEnc::stringToChunkArray(const string& str) {
  Logger::log(MessageType::DEBUG, "RSAEnc", "Converting string to chunk array ...");
  Logger::log(MessageType::DEBUG, "Encrypting", str);

  // Make single array of bits
  vector<bool> bits;
  for (char c : str) {
    bitset<8> b(c);
    for (int i = 7; i >= 0; --i) {
      bits.push_back(b[i]);
    }
  }
  Logger::log(MessageType::DEBUG, "Bits", bits.size());
  Logger::log(MessageType::DEBUG, "Bits", bits);

  // Split bits into chunks (random size)
  vector<int> chunks;
  size_t next_chunk = 0;
  while (next_chunk < bits.size()) {
    size_t chunk_size = randomInt(2, k/2); // Random chunk size
    // Adjust chunk size if it exceeds the remaining bits
    if (next_chunk + chunk_size > bits.size()) { 
      chunk_size = bits.size() - next_chunk;
    }
    vector<bool> chunk;
    chunk.push_back(true); // Start with a 1
    vector<bool> chunk_bits(bits.begin() + next_chunk, bits.begin() + min(next_chunk + chunk_size, bits.size()));
    for (bool bit : chunk_bits) {
      chunk.push_back(bit);
    }
    chunks.push_back(binToDec(chunk));
    next_chunk += chunk_size;
    Logger::log(MessageType::DEBUG, "Chunk", chunk);
    Logger::log(MessageType::DEBUG, "Chunk Value", chunks.back());
  }

  return chunks;
}


vector<bool> RSAEnc::chunkArrayToBits(const vector<int>& chunks) {
  vector<bool> bits;
  for (int value : chunks) {
    Logger::log(MessageType::VERBOSE, "Value", value);
    vector<bool> value_bits = decToBin(value);
    Logger::log(MessageType::VERBOSE, "Value bits", value_bits);
    for (bool bit : value_bits) {
      bits.push_back(bit);
    }
  }
  return bits;
}

// vector<vector<bool>> RSAEnc::splitBitArray(const vector<bool>& bits) {
  
// }

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

  setPrimeBitLength();
}

RSAEnc::RSAEnc(long long p, long long q, long long e_val) : p(p), q(q) {
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
  setPrimeBitLength();
}

vector<bool> RSAEnc::encrypt(const string& message) {
  // Logger::log(MessageType::INFO, "RSAEnc", "Encrypting message ...");
  // Logger::log(MessageType::INFO, "Message", message);
  // Logger::log(MessageType::INFO, "Bits", bits.size());
  // Logger::log(MessageType::INFO, "Bits", bits);
  // Logger::blank(MessageType::INFO);

  // vector<vector<bool>> splitBits = splitBitArray(bits);
  // vector<int> chunkValues;
  // Logger::log(MessageType::INFO, "k", k);
  // for (vector<bool> chunk : splitBits) {
  //   Logger::log(MessageType::INFO, "Chunk", chunk.size());
  //   Logger::log(MessageType::INFO, "Chunk", chunk);
  //   chunkValues.push_back(binToDec(chunk));
  //   Logger::log(MessageType::INFO, "Chunk Value", chunkValues.back());
  // }


  vector<int> chunk_values = stringToChunkArray(message);
  Logger::log(MessageType::INFO, "Chunk Values", chunk_values);
  IntMod::setDefaultModulus(n);
  vector<int> encrypted_chunk_values;
  for (int value : chunk_values) {
    IntMod a(value);
    IntMod b = a.pow((int) e);
    Logger::log(MessageType::INFO, "Encrypted Chunk", b);
    encrypted_chunk_values.push_back((int) b);
  }
  
  vector<bool> bits = chunkArrayToBits(encrypted_chunk_values);
  Logger::log(MessageType::DEBUG, "Encrypted Message", bits);
  return bits;
}