#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include<iostream>
#include <string.h>
#include<gmp.h>
using namespace std;


void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;
  int len,ciphertext_len;

  if(!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    handleErrors();
  ciphertext_len += len;

  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int main()
{
  // cout<<"hrer";
  mpz_t i,keytemp,r;
  int j=3;
  mpz_inits(i,keytemp,r,NULL);
  mpz_set_ui(keytemp,32766);
  char *key=mpz_get_str(NULL,10,keytemp);
  cout<<"here 1\n";
  // unsigned char *key = (unsigned char *)"01234567890123456789012345678901";   /* A 256 bit key */
  unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit key */
  // unsigned char *plaintext =(unsigned char *)"The quick brown fox jumps over the lazy dog";

  string te=to_string(j);
  const char *plaintext = te.c_str();
  cout<<"here 2\n";
  unsigned char *ciphertext;

  int  ciphertext_len,k;

  // (unsigned char *plaintext, int plaintext_len, unsigned char *key,unsigned char *iv, unsigned char *cip
  ciphertext_len = encrypt ((unsigned char*)plaintext, strlen(plaintext),(unsigned char*) key, iv,ciphertext);
  cout<<"here 3\n"<<ciphertext_len<<endl<<ciphertext<<endl;
  for (k = 0;k < ciphertext_len; k++){
    cout<<"here 4\n";
    if((int)ciphertext[k]>=100)
    {
      cout<<"here 5\n";
      // mpz_clear(r);
      mpz_init(r);
      mpz_set_ui(r,1000);
      // mpz_clear(r);
      cout<<"here 6\n";
    }
    else{
      cout<<"here 7\n";
      // mpz_set_ui(r,100);
      // mpz_clear(r);
      mpz_init(r);
      mpz_set_ui(r,100);
      
    }
    mpz_mul(i,i,r);
    mpz_add_ui(i,i,(int)ciphertext[k]);
  }

}
