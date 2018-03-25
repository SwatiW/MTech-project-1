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
#include "random_num.cpp"
int gen_random_no(int out,int bit_cnt,mpz_t max_no,mpz_t rand_no);

int main() {
  mpz_t c,k1,k2,s,gs,g,n,r_max,k;
  mpz_inits(c,k1,k2,s,g,gs,n,r_max,k,NULL);

  mpz_set_ui(r_max,1000);                           // 0 <= c < f(total no of file blocks)
  gen_random_no(2,0,r_max,c);                // generate c

  mpz_set_ui(r_max,0);
  gen_random_no(1,16,r_max,k1);              //  generate k1
  gen_random_no(1,20,r_max,k2);              // generate k2


  gen_random_no(1,16,r_max,s);
  gen_random_no(1,20,r_max,g);
  gen_random_no(1,20,r_max,n);
  mpz_powm(gs,g,s,n);         // gs = g^s mod n

  gmp_printf("k1 => %Zd\nk2 => %Zd\n s => %Zd\n c => %Zd\n",k1,k2,s,c);
  return 0;
}




// to do ---
/*
  change bitcnt for all random nos.
  g and n are taken from keygen algorithms
  for c to generate , r_max should be f
  remove n,g from initializations
*/
