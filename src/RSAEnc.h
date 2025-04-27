#ifndef RSAENC_H
#define RSAENC_H

#include <iostream>
#include "IntMod.h"

class RSAEnc
{
private:
  long long p, q, n, phi;
  IntMod e, d;
public:
  RSAEnc();
  RSAEnc(long long p, long long q);
};



#endif