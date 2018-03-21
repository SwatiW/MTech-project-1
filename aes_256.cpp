#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include<iostream>
#include <string.h>
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


int main (void)
{
  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";   /* A 256 bit key */
  unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit key */

  unsigned char *plaintext =(unsigned char *)"The quick brown fox jumps over the lazy dog";

  unsigned char ciphertext[128];

  int  ciphertext_len;
  ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,ciphertext);

  printf("Ciphertext is:\n");
  for(int i=0;i<ciphertext_len;i++)
    printf("%02x", (int)ciphertext[i]);


  return 0;

}
