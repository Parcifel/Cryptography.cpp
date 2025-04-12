#include <iostream>
using namespace std;

#include "Poly.h"
#include "IntMod.h"
#include "Logger.h"
#include "Helper.h"

int main() {
  Logger::log(MessageType::SUCCESS, "System", "Application started");

  IntMod::setDefaultModulus(37);
  IntMod a1 = IntMod(2);
  int e1 = 19;
  int e2 = 12;


  Logger::log(MessageType::INFO, "", "g = " + a1.toString());
  cout << "g = " << a1 << endl;
  cout << "e1 = " << e1 << endl;
  cout << "e2 = " << e2 << endl;
  IntMod B = a1.pow(e1);
  cout << "B = " << B << endl;
  IntMod S = B.pow(12);
  IntMod AB = a1.pow(e1*e2);
  cout << "S = " << S << endl;
  cout << "AB = " << AB << endl;

  Logger::log(MessageType::DEBUG, "", IntMod(2, 3));

  int d = euclidAlgo(4864, 3458);
  Logger::log(MessageType::INFO, "Euclidean Algo", "gcd(4864, 3458) = " + to_string(d));
  vector<int> D = extendedEuclidAlgo(29, 11);
  vector<vector<int>> D_tab = {D};

  Logger::table(MessageType::INFO, "Extended Euclidean Algo", {}, D_tab);

  Logger::log(MessageType::SUCCESS, "System", "Application finished");
  return 0;
}