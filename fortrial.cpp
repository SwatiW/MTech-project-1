#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include<gmp.h>
#include <iostream>
#include "random_num.cpp"

using namespace std;
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len,ciphertext_len;
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  // if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
  //   handleErrors();
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key,NULL))
    handleErrors();

  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;
cout<<"1plain - "<<plaintext<<endl<<"cipher - "<<ciphertext<<" length - "<<ciphertext_len<<endl;

  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;
  cout<<"2plain - "<<plaintext<<endl<<"cipher - "<<ciphertext<<" length - "<<ciphertext_len<<endl;

  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}
int main (void)
{
  mpz_t ke,iv_temp,r_max,r,store;
  mpz_inits(ke,iv_temp,r_max,r,store,NULL);
  mpz_set_ui(ke,31441);
//   mpz_set_ui(iv_temp,245440057249045995831877827754909624469);
  char *key = mpz_get_str(NULL,10,ke);
  int j=0,k;
  string s=to_string(j);
  const char *plaintext =s.c_str();
  unsigned long int seed;
  gmp_randstate_t r_state;
  seed = time(NULL);
  gmp_randinit_default (r_state);
  gmp_randseed_ui(r_state, seed);
  // unsigned char *plaintext =(unsigned char *)"The quick brown fox jumps over the lazy dog";

  gen_random_no(1,128,r_max,iv_temp,r_state);
  char *iv = mpz_get_str(NULL,10,iv_temp);
  // unsigned char *iv = (unsigned char *)"0123456789012345";
  unsigned char ciphertext[128];
  unsigned char decryptedtext[128];
  int decryptedtext_len, ciphertext_len;
  ciphertext_len = encrypt ((unsigned char *)plaintext, strlen ((char *)plaintext),(unsigned char *) key, (unsigned char *)iv,ciphertext);
  // printf("Ciphertext is:\n");
  // BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
  for (k = 0;k < ciphertext_len; k++){
    if((int)ciphertext[k]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(store,store,r);
    mpz_add_ui(store,store,(int)ciphertext[k]);
  }
  gmp_printf("plain - %d\t cipher - %Zd\n",j,store);

  return 0;
}
