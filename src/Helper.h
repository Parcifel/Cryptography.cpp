#ifndef HELPER_H
#define HELPER

template<typename T>
vector<T> reverse(const vector<T>& v);
int binToDec(const vector<bool>& bits);
vector<bool> decToBin(int n, int k);
vector<bool> decToBin(int n);
int randomInt(int min, int max);
long long euclidAlgo(long long a, long long b);
vector<long long> extendedEuclidAlgo(long long a, long long b);
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