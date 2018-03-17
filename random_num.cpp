// generating a random no.
// get bit_cnt || max_no from other programs to generate a random no.
// the program returns rand_no

// #include "all_functions.h"
#include<iostream>
#include<gmp.h>
#include<time.h>

int gen_random_no(int out,int bit_cnt,mpz_t max_no,mpz_t rand_no)
{

  mpz_inits(rand_no,NULL);

  unsigned long int seed;
  gmp_randstate_t r_state;
  seed = time(NULL);
  gmp_randinit_default (r_state);
  gmp_randseed_ui(r_state, seed);

  if(out==1)
    mpz_urandomb (rand_no,r_state,bit_cnt);
  // 1. void mpz_urandomb (mpz t rop , gmp randstate t state , mp bitcnt t n )
  // Generate a uniformly distributed random integer in the range 0 to 2 n − 1, inclusive.

  if(out==2)
    mpz_urandomm (rand_no,r_state,max_no);
  // 2. void mpz_urandomm (mpz t rop , gmp randstate t state , const mpz t n )
  // Generate a uniform random integer in the range 0 to n − 1, inclusive.

  if(out==3)
    mpz_rrandomb (rand_no ,r_state,bit_cnt);
  // 3. void mpz_rrandomb (mpz t rop , gmp randstate t state , mp bitcnt t n )
  // Generate a random integer with long strings of zeros and ones in the binary representation.
  // Useful for testing functions and algorithms, since this kind of random numbers have proven
  // to be more likely to trigger corner-case bugs. The random number will be in the range 0 to
  // 2 n − 1, inclusive.

  return 0;
}
