#include<iostream>
#include<gmp.h>
#include<time.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;
#include "../crypto_funcs/sha1.cpp"
#include "../crypto_funcs/hmac.cpp"
#include "../crypto_funcs/aes.cpp"
mpz_t n,c,k1,k2,gs,b[25],tag[25];
void read_n_c_k1_k2();
void read_tag_block();
void HASH(mpz_t to_be_hashed,mpz_t hash_val);
void PRF(mpz_t a,mpz_t key,int j);
void PRP(mpz_t i,mpz_t key,int j);

int main(){
  mpz_t T,temp,ex,rho,hashed_val,f;
  mpz_inits(T,temp,ex,rho,hashed_val,c,k1,k2,n,gs,f,NULL);
  read_n_c_k1_k2();
  int j=0,jt,itr,te;
  mpz_t i[mpz_get_ui(c)],a[mpz_get_ui(c)];
  mpz_set_ui(f,25);
  for (itr = 0; itr < mpz_get_ui(c); itr++) {
    mpz_inits(i[itr],a[itr],NULL);
  }
  j=0;
  // gmp_printf("j\ti\ta\n");
  while(mpz_cmp_ui(c,j)>0){
    PRP(i[j],k1,j);
    PRF(a[j],k2,j);
    mpz_mod(i[j],i[j],f);
    mpz_mod(a[j],a[j],f);
    // gmp_printf("%d\t%Zd\t%Zd\n",j,i[j],a[j]);
    j++;
  }

  read_tag_block();
  j=0;
  mpz_set_ui(T,1);
  while(mpz_cmp_ui(c,j)>0){
    te=mpz_get_ui(i[j]);
    // gmp_printf("%d\t%Zd\t%Zd\n",te,tag[te],b[te]);
    mpz_powm(temp,tag[te],a[j],n);
    mpz_mul(T,T,temp);                              //calculate T
    mpz_mod(T,T,n);

    mpz_mul(temp,b[te],a[j]);
    mpz_add(ex,ex,temp);
    mpz_mod(ex,ex,n);
    j++;
  }
  // //
  mpz_powm(temp,gs,ex,n);
  HASH(temp,hashed_val);
  mpz_set(rho,hashed_val);

   // (T,rho) is the proof generated
  gmp_printf("T %Zd\nrho %Zd\n",T,rho);

  return 0;
}


void read_n_c_k1_k2(){
  fstream key_file,key2_file;
  string word,filename,n_keygen,k1_gen,k2_gen,c_gen,gs_gen;
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
  filename = "../outputs/gen_chal_out.txt";
  key2_file.open(filename.c_str());
  i=1;
  while (key2_file >> word)
  {
      if(i%18==0)
        gs_gen=word;
      else if(i%12==0)
        c_gen=word;
      else if(i%6==0)
        k2_gen=word;
      else if(i%3==0)
        k1_gen=word;
      i++;
  }
  mpz_set_str (n,n_keygen.c_str(),10);
  mpz_set_str (gs,gs_gen.c_str(),10);
  mpz_set_str (k1,k1_gen.c_str(),10);
  mpz_set_str (k2,k2_gen.c_str(),10);
  mpz_set_str (c,c_gen.c_str(),10);
  // gmp_printf("\nn - %Zd\nk1 - %Zd\nk2 - %Zd\nc - %Zd\ngs - %Zd\n",n,k1,k2,c,gs);

}

void read_tag_block(){
  fstream key_file,key2_file;
  string word,filename,tagtemp,blocktemp;
  // read values from keygen and file_blocks
  filename = "../outputs/tag_block_out.txt";
  key_file.open(filename.c_str());
  int it=0;
  while (!key_file.eof())
  {
      key_file >> word;
      key_file >> blocktemp;
      mpz_set_str(b[it],blocktemp.c_str(),10);
      key_file >> tagtemp;
      mpz_set_str(tag[it],tagtemp.c_str(),10);
      it++;
  }

}
