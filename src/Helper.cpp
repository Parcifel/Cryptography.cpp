#include <iostream>
#include "Logger.h"
#include "IntMod.h"
#include <random>
#include <fstream>
#include <string>


int randomInt(int min, int max) {
  static random_device rd;
  static mt19937 gen(rd());
  uniform_int_distribution<> distrib(min, max);
  return distrib(gen);
}

/**
 * @brief Gets the gcd(a, b) with a < b
 * 
 * @param a
 * @param b
 * @return
 */
int euclidAlgo(int a, int b) {
  if (b > a) {
    throw invalid_argument("Expected a <= b, got a = " + to_string(a) + " and  b = " + to_string(b)); 
  }

  // == for debug output ==
  vector<vector<int>> table;
  // == ==

  int r = 1;
  while (b != 0) {
    r = a % b;
    table.push_back({a, b, r});
    a = b;
    b = r;
  }

  // == verbose output ==
  Logger::blank(MessageType::VERBOSE, 2);
  Logger::table(
    MessageType::VERBOSE, 
    "Euclidean Algorithm (" + to_string(a) + ", " + to_string(b) + ")", 
    {"a", "b", "r"}, 
    table
  );
  Logger::log(MessageType::VERBOSE, "Output", a);
  Logger::blank(MessageType::VERBOSE);
  // == ==
   
  return a;
}

/**
 * @brief Gets the gcd(a, b) with a < b
 * output[0]: d = gcd(a, b)
 * output[1]: x
 * output[2]: y
 * such that a*x + b*y = d
 * 
 * @param a
 * @param b
 * @return a vector with a few output values as described in the description
 */
vector<int> extendedEuclidAlgo(int a, int b) {
  if (b > a) {
    throw invalid_argument("Expected a <= b, got a = " + to_string(a) + " and  b = " + to_string(b)); 
  }

  // == for debug output ==
  //  this can be optimised to not store the whole table but only 2 or 3 rows at a time
  vector<vector<int>> table;
  vector<int> row = {0, 0, 0, 0};
  // == ==

  row = {0, a, 1, 0};
  table.push_back(row);
  row = {0, b, 0, 1};
  table.push_back(row);

  int q, r, x, y;
  int i = 1;
  while (table[i][1] != 0) {                  // r[i] != 0
    i++;
    q = (int) (table[i-2][1] / table[i-1][1]);// r[i-2] / r[i-1]
    r = table[i-2][1] - q * table[i-1][1];    // r[i-2] - q[i] * r[i-1]
    x = table[i-2][2] - q * table[i-1][2];    // x[i-2] - q[i] * x[i-1]
    y = table[i-2][3] - q * table[i-1][3];    // y[i-2] - q[i] * y[i-1]
    row = {q, r, x, y};
    table.push_back(row);
  }

  vector<int> result = {table[i-1][1], table[i-1][2], table[i-1][3]};

  // == for verbose output ==
  Logger::blank(MessageType::DEBUG, 2);
  Logger::table(
    MessageType::VERBOSE, 
    "Extended Euclidean Algorithm (" + to_string(a) + ", " + to_string(b) + ")", 
    {"q", "r", "x", "y"}, 
    table
  );
  Logger::log(MessageType::DEBUG, "d", to_string(result[0]));
  Logger::log(MessageType::DEBUG, "x", to_string(result[1]));
  Logger::log(MessageType::DEBUG, "y", to_string(result[2]));
  Logger::log(
    MessageType::VERBOSE, 
    "result",
    to_string(a) + "*" + to_string(result[1]) + " + " + to_string(b) + "*" + to_string(result[2]) + " = " + to_string(result[0]) 
  );
  Logger::blank(MessageType::DEBUG);
  // == ==

  return result;
}

/**
 * Uses the Miller Radin Test to calculate if a number is probabilisticly a prime
 */
// bool isPrime(int p) {
//   if (p <= 0) {
//     throw invalid_argument("Value cannot be <= 0.");
//   }

//   if (p == 1)     return false;
//   if (p <= 3)     return true;
//   if (p % 2 == 0) return false;

//   int d = p - 1;
//   int s = 0;
//   while (d % 2 == 0) {
//     d /= 2;
//     s++;
//   }

//   int k = 5;
//   for (int i = 0; i < k; i++) {
//     int a = 2 + rand() % (p - 3);

//     IntMod base(a, p);
//     IntMod x = base.pow(d);

//     if (x == 1 || x == p-1) continue;

//     bool composite = true;
//     for (int r = 1; r < s; r++) {
//       x = x * x;
//       if (x == 1) return false;
//       if (x == p-1) {
//         composite = false;
//         break;
//       }
//     }

//     if (composite) return false;
//   }
//   return true;
// }

/**
 * Uses trial division approach
 */
bool isPrime(int p) {
  if (p == 1)     return false; // p = 1
  if (p <= 3)     return true;  // p = 2 or 3
  if (p % 2 == 0) return false; // p := even

  int n = ceil((int) sqrt(p));
  for (int i = 3; i <= n; i+= 2) {
    if ((p % i) == 0) return false;
  }

  return true;
}

vector<vector<int>> primeFactorization(int p) {
  vector<vector<int>> result = {};

  if (p <= 1) {
    return result;
  }
  if (p == 2) {
    vector<int> row = {2, 1};
    result.push_back(row);
    // result[1].push_back(1);
    return result;
  }

  int index = 0;

  // 2 is the only even prime number
  if ((p % 2) == 0) {
    result.push_back({2, 0});
    index++;
  }
  while ((p % 2) == 0) {
    result[index-1][1]++;
    p /= 2;
  }

  int i = 3;
  while (p > 1) {
    if ((p % i) == 0) {
      result.push_back({i, 0});
      index++;
    }
    while ((p % i) == 0) {
      result[index-1][1]++;
      p /= i;
    }

    i += 2;
  }
  
  return result;
}

int eulerPhi(int n) {
  if (n < 1) {
    throw invalid_argument("Euler Phi function only takes integers >= 1");
  }

  if (isPrime(n)) {
    return n-1;
  }

  vector<vector<int>> primeFactors = primeFactorization(n);
  Logger::table(MessageType::INFO, "Prime Factors", {"p", "e"}, primeFactors);
  double phi = (double) n;

  for (vector<int> factor : primeFactors) {
    phi *= (1.0 - 1.0/(double)factor[0]);
  }
  return (int)phi;
}

int findGenerator(int p) {
  int n = p-1;
  vector<vector<int>> primeFactors = primeFactorization(n);
  Logger::log(MessageType::INFO, "n", n);
  Logger::table(MessageType::INFO, "Prim Factors", {"p", "e"}, primeFactors);

  int g;
  IntMod::setDefaultModulus(p);
  while (true) {
    g = 2 + rand() % n-2;
    IntMod a(g);
    IntMod b(0);
    if (a == 0 || a == 1) continue;
    for (size_t i = 0; i < primeFactors.size(); i++) {
      b = a.pow((int) (n / primeFactors[i][0]));
      if (b == 1) break;
    }
    if (b != 1) break; 
  }

  return g;
}

/**
 * Determines if a file exists
 */
bool fileExists(string filename) {
  ifstream f(filename);
  return f.good();
}

/**
 * generates a file with predefined "small primes"
 * this can be used in differnet functions
 * @param k
 */
void generateSmallPrimes(int k) {
  if (k < 2 || k > 31) {
    throw invalid_argument("k must be between 2 and 31 (inclusive)");
  }

  string filename("small_primes_" + to_string(k) + ".csv");
  if (fileExists(filename)) {
    return;
  }
  ofstream out(filename);
  if (!out.is_open()) {
    throw runtime_error("Could not open small_primes.csv for writing");
  }

  int maxNum = (1 << k) -1;
  for (int i = 2; i <= maxNum; i++) {
    if (isPrime(i)) {
      out << i << "\n";
    }
  }

  out.close();
  Logger::log(
    MessageType::SUCCESS, 
    "Small Primes Generated", 
    "Finished generating small primes up to " + to_string(maxNum)
  );
}

size_t countPrimes(int min, int max, int k) {
  string filename("small_primes_" + to_string(k) + ".csv");
  if (!fileExists(filename)) {
    generateSmallPrimes(k);
  }

  ifstream in(filename);
  string line;
  size_t c = 0;

  if (!in.is_open()) {
    cerr << "Could not open file: " << filename << endl;
  }

  while (getline(in, line)) {
    stringstream ss(line);
    string cell;

    int val;
    if (ss >> val) {
      if (min <= val && val <= max) {
        c += 1;
      }
    }
  }

  return c;
}

int fetchSmallPrime(int min, int k, int index) {
  string filename("small_primes_" + to_string(k) + ".csv");
  if (!fileExists(filename)) {
    generateSmallPrimes(k);
  }

  ifstream in(filename);
  string line;
  size_t i = 0;

  if (!in.is_open()) {
    cerr << "Could not open file: " << filename << endl;
  }

  while (getline(in, line)) {
    stringstream ss(line);
    string cell;

    int val;
    if (ss >> val) {
      if (min <= val) {
        Logger::log(MessageType::DEBUG, "Bigger Val", i);
        if ((int) i == index) {
          return val;
        }
        i += 1;
      }
    }
  }

  return -1;
}

/**
 * Generates a random prime with k bits
 *   Uses small primes file with primes less than or equal to 20 bits
 */
long generatePrime(int k) {
  if (k < 2 || k > 63) {
    throw invalid_argument("k must be between 2 and 63 (inclusive)");
  }

  long minNum = (1 << (k - 1));
  long maxNum = (1 << (k)) - 1;

  // small primes approach
  if (k <= 20) {
    // count primes
    size_t c = countPrimes(minNum, maxNum, k);
    int index = randomInt(0, (int) c - 1);
    Logger::log(MessageType::DEBUG, "Index", index);
    long p = (long) fetchSmallPrime(minNum, k, index);
    if (p < minNum || maxNum < p) {
      Logger::log(
        MessageType::ERROR, 
        "Prime out of bounds", 
        to_string(p) + " not in [" + to_string(minNum) + ", " + to_string(maxNum) + "]"
      );
      return -1;
    }
    return p;
  }

  return -1;
}
