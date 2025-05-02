#ifndef RSAENC_H
#define RSAENC_H

#include <iostream>
#include <vector>
#include <string>
#include "IntMod.h"

using namespace std;

class RSAEnc
{
private:
  long long p, q, n, phi;
  int k;
  IntMod e, d;

  void setPrimeBitLength();
  vector<int> stringToChunkArray(const string& str);
  vector<bool> chunkArrayToBits(const vector<int>& chunks);
  string chunkArrayToString(const vector<int>& chunks);
  vector<int> bitsToChunkArray(const vector<bool>& bits);
public:
  RSAEnc();
  RSAEnc(long long p, long long q);
  RSAEnc(long long p, long long q, long long e_val);

  vector<bool> encrypt(const string& message);
  string decrypt(const vector<bool>& bits);
};



#endif