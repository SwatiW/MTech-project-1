#include <openssl/hmac.h>
#include <stdio.h>
#include <string.h>
// #include<iostream>
#include<gmp.h>
#include<time.h>
// using namespace std;
// #include<iostream>

// using namespace std;



int main(){
  mpz_t temp,r,key,hash_val;
  mpz_inits(temp,r,key,hash_val,NULL);

  unsigned long int seed;
  gmp_randstate_t r_state;
  seed = time(NULL);
  gmp_randinit_default (r_state);
  gmp_randseed_ui(r_state, seed);
  mpz_urandomb (key,r_state,20);

  unsigned char data[]="1";
  int i;
  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hashlen;
  HMAC(EVP_sha1(),key,sizeof(key),data,strlen(data),hash,&hashlen);
   // print_hex(hash,hashlen);

  for (i = 0; i < hashlen; i++){
    if((int)hash[i]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(hash_val,hash_val,r);
    mpz_add_ui(hash_val,hash_val,(int)hash[i]);
  }
  gmp_printf("%Zd\n",hash_val);
  return 0;
}
