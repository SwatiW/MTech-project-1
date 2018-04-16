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
#include<fstream>
// #include "all_functions.h"
using namespace std;
#include "../random_num.cpp"
int gen_random_no(int out,int bit_cnt,mpz_t max_no,mpz_t rand_no,gmp_randstate_t r_state1);
mpz_t n;
void read_n();

int main() {
  mpz_t c,k1,k2,s,gs,g,r_max,k;
  mpz_inits(c,k1,k2,s,g,gs,n,r_max,k,NULL);
  read_n();

  unsigned long int seed;
  gmp_randstate_t r_state;
  seed = time(NULL);
  gmp_randinit_default (r_state);
  gmp_randseed_ui(r_state, seed);

  mpz_set_ui(r_max,1000);                           // 0 <= c < f(total no of file blocks)
  gen_random_no(2,0,r_max,c,r_state);                // generate c

  mpz_set_ui(r_max,0);
  gen_random_no(1,16,r_max,k1,r_state);              //  generate k1
  gen_random_no(1,20,r_max,k2,r_state);              // generate k2


  gen_random_no(1,16,r_max,s,r_state);
  gen_random_no(1,20,r_max,g,r_state);
  // gen_random_no(1,20,r_max,n);
  mpz_powm(gs,g,s,n);         // gs = g^s mod n

  gmp_printf("k1 => %Zd\nk2 => %Zd\n s => %Zd\n c => %Zd\n g => %Zd\n gs => %Zd\n",k1,k2,s,c,g,gs);
  return 0;
}

void read_n(){

  fstream key_file;
  string word,filename,n_keygen;
  // read values from keygen and file_blocks
  filename = "../outputs/key_gen_out.txt";
  key_file.open(filename.c_str());
  int i=1;
  while (key_file >> word)
  {
      if(i%3==0 && i%6!=0 && i%9!=0 && i%12!=0)
        n_keygen=word;
      i++;
  }
  mpz_set_str (n,n_keygen.c_str(),10);
}



// to do ---
/*
  change bitcnt for all random nos.
  g and n are taken from keygen algorithms
  for c to generate , r_max should be f
  remove n,g from initializations
*/
