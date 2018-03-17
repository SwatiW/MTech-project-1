//  generate challenge to be sent to the storage provider
//  chal = (c,k1,k2,gs)
//  c => no of blocks
//  s => random no
//  k1 => random no.
//  k2 => random no.
//  gs => g^s
//  g => generator , take g and n from keygen
//  k => security parameter

#include<iostream>
#include<gmp.h>
#include<time.h>
// #include "all_functions.h"
#include "random_number.cpp"
int gen_random_no(int out,int bit_cnt,mpz_t max_no,mpz_t rand_no);

int main() {
  mpz_t c,k1,k2,s,gs,r_max,k;
  mpz_inits(c,k1,k2,s,gs,r_max,k,NULL);

  mpz_set(r_max,f);                           // 0 <= c < f(total no of file blocks)
  gen_random_no(2,k,r_max,c);                // generate c

  mpz_set_ui(r_max,0);
  gen_random_no(1,k,r_max,k1);              //  generate k1
  gen_random_no(1,k,r_max,k2);              // generate k2
  gmp_printf("%Zd\n%Zd\n",k1,k2);

  mpz_powm(gs,g,s,n);         // gs = g^s mod n

  return 0;
}
