#ifndef HELPER_H
#define HELPER

#include <iostream>
#include "Logger.h"

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

  int r = 1;
  while (b != 0) {
    r = a % b;
    a = b;
    b = r;
  }
   
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

  vector<vector<int>> table;
  vector<int> row = {0, 0, 0, 0};

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

  Logger::table(
    MessageType::DEBUG, 
    "Extended Euclidean Algorithm (" + to_string(a) + ", " + to_string(b) + ")", 
    {"q", "r", "x", "y"}, 
    table
  );

  vector<int> result = {table[i-1][1], table[i-1][2], table[i-1][3]};
  return result;
}

#endif