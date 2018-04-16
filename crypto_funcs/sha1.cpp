void HASH(mpz_t to_be_hashed,mpz_t hash_val){
  string msg;
  EVP_MD_CTX *ctx;
  const EVP_MD *md;
  mpz_t temp,r;
  mpz_inits(temp,r,NULL);
  mpz_set(temp,to_be_hashed);
  int r_int,i;

  while(mpz_cmp_ui(temp,0)!=0){
    mpz_fdiv_qr_ui(temp,r,temp,100);
    r_int=mpz_get_ui(r);
    // cout<<r_int<<" - ";
    msg+=(char)r_int;
    // cout<<msg<<endl;
    // msg+=to_string(r);
  }

  char *msg_to_hash;
  // cout<<"msg in c string => "<<msg<<endl;
  msg_to_hash=(char *) malloc(1+msg.length());
  strcpy(msg_to_hash,msg.c_str());

  unsigned char md_val[EVP_MAX_MD_SIZE];
  unsigned int mdlen;
  md=EVP_sha1();
  ctx=EVP_MD_CTX_create();

  EVP_DigestInit_ex(ctx,md,NULL);
  EVP_DigestUpdate(ctx,msg_to_hash,strlen(msg_to_hash));
  EVP_DigestFinal(ctx,md_val,&mdlen);
  for (i = 0; i < mdlen; i++){
    if((int)md_val[i]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(hash_val,hash_val,r);
    mpz_add_ui(hash_val,hash_val,(int)md_val[i]);
  }
  // gmp_printf("%Zd\n%Zd\n",to_be_hashed,hash_val);
}




/*// sha1.cpp - working => in- to_be_hashed, out - hash_val


#include <openssl/evp.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<gmp.h>
#include<time.h>
using namespace std;

int main(){
  EVP_MD_CTX *ctx;
  const EVP_MD *md;
  char *msg_to_hash;
  unsigned char md_val[EVP_MAX_MD_SIZE];
  unsigned int mdlen;
  md=EVP_sha1();
  ctx=EVP_MD_CTX_create();

  string msg;
  int r_int;
  mpz_t temp,r,to_be_hashed,hash_val;
  mpz_inits(temp,r,to_be_hashed,hash_val,NULL);

  unsigned long int seed;
  gmp_randstate_t r_state;
  seed = time(NULL);
  gmp_randinit_default (r_state);
  gmp_randseed_ui(r_state, seed);
  mpz_urandomb (to_be_hashed,r_state,20);
  gmp_printf("to_be_hashed => %Zd\n",to_be_hashed);
  mpz_set(temp,to_be_hashed);
  while(mpz_cmp_ui(temp,0)!=0){
    mpz_fdiv_qr_ui(temp,r,temp,100);
    r_int=mpz_get_ui(r);
    cout<<r_int<<" - ";
    msg+=(char)r_int;
    cout<<msg<<endl;
    // msg+=to_string(r);
  }

  cout<<"msg in c string => "<<msg<<endl;
  msg_to_hash=(char *) malloc(1+msg.length());
  strcpy(msg_to_hash,msg.c_str());

  EVP_DigestInit_ex(ctx,md,NULL);
  EVP_DigestUpdate(ctx,msg_to_hash,strlen(msg_to_hash));
  EVP_DigestFinal(ctx,md_val,&mdlen);
  int i;

  for (i = 0; i < mdlen; i++){
    if((int)md_val[i]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(hash_val,hash_val,r);
    mpz_add_ui(hash_val,hash_val,(int)md_val[i]);
  }
  gmp_printf("\n%Zd\n",hash_val);
  return 0;
}
*/
