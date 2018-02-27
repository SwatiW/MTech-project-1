#include <openssl/evp.h>
#include<stdio.h>
#include<string.h>

void print_hex(unsigned char *md_val, unsigned int mdlen)
{
 int i;
 for (i = 0; i < mdlen; i++)
 printf("%02x", md_val[i]);
}

int main(){
  EVP_MD_CTX *ctx;
  const EVP_MD *md;
  char msg[]="hgk World";
  unsigned char md_val[EVP_MAX_MD_SIZE];
  int mdlen;
  md=EVP_sha1();
  ctx=EVP_MD_CTX_create();

  EVP_DigestInit_ex(ctx,md,NULL);
  EVP_DigestUpdate(ctx,msg,strlen(msg));
  EVP_DigestFinal(ctx,md_val,&mdlen);
  print_hex(md_val,mdlen);
  printf("\n");
  return 0;
}
