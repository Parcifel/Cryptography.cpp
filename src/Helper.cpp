#include <iostream>
#include "Logger.h"
#include "IntMod.h"
#include <random>

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

  // == debug output ==
  Logger::blank(2);
  Logger::table(
    MessageType::DEBUG, 
    "Euclidean Algorithm (" + to_string(a) + ", " + to_string(b) + ")", 
    {"a", "b", "r"}, 
    table
  );
  Logger::log(MessageType::DEBUG, "Output", a);
  Logger::blank();
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

  // == for debug output ==
  Logger::blank(2);
  Logger::table(
    MessageType::DEBUG, 
    "Extended Euclidean Algorithm (" + to_string(a) + ", " + to_string(b) + ")", 
    {"q", "r", "x", "y"}, 
    table
  );
  Logger::log(MessageType::DEBUG, "d", to_string(result[0]));
  Logger::log(MessageType::DEBUG, "x", to_string(result[1]));
  Logger::log(MessageType::DEBUG, "y", to_string(result[2]));
  Logger::log(
    MessageType::DEBUG, 
    "result",
    to_string(a) + "*" + to_string(result[1]) + " + " + to_string(b) + "*" + to_string(result[2]) + " = " + to_string(result[0]) 
  );
  Logger::blank();
  // == ==

  return result;
}

/**
 * Uses the Miller Radin Test to calculate if a number is prime
 */
bool isPrime(int p) {
  if (p <= 0) {
    throw invalid_argument("Value cannot be <= 0.");
  }

  if (p == 1)     return false;
  if (p <= 3)     return true;
  if (p % 2 == 0) return false;

  int d = p - 1;
  int s = 0;
  while (d % 2 == 0) {
    d /= 2;
    s++;
  }

  int k = 5;
  for (int i = 0; i < k; i++) {
    int a = 2 + rand() % (p - 3);

    IntMod base(a, p);
    IntMod x = base.pow(d);

    if (x == 1 || x == p-1) continue;

    bool composite = true;
    for (int r = 1; r < s; r++) {
      x = x * x;
      if (x == 1) return false;
      if (x == p-1) {
        composite = false;
        break;
      }
    }

      if (composite) return false;
  }
  return true;
}