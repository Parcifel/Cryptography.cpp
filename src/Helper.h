#ifndef HELPER_H
#define HELPER

int randomInt(int min, int max);
int euclidAlgo(int a, int b);
vector<int> extendedEuclidAlgo(int a, int b);
bool isPrime(int p);
vector<vector<int>> primeFactorization(int p);
int findGenerator(int p);
int eulerPhi(int n);
void generateSmallPrimes(int k);
bool fileExists(string filename);
int countPrimes(int min, int max, int k);
int fetchSmallPrime(int min, int k, int index);
long generatePrime(int k);
long long generateEncExp(long long phi);

#endif