//get (rho,T) from the service provider

#include<iostream>
#include<gmp.h>
#include<time.h>
#include<string.h>
#include<openssl/md5.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
using namespace std;
#include "../crypto_funcs/sha1.cpp"
#include "../crypto_funcs/aes.cpp"
#include "../crypto_funcs/simple_hash.cpp"
#include "../crypto_funcs/hmac.cpp"

mpz_t n,c,k1,k2,v,s,e,g,T,rho;

void read_all();

int main(){

  mpz_t temp,hashed_val,f;
  mpz_inits(temp,hashed_val,n,s,c,k1,k2,v,e,g,T,rho,f,NULL);
  read_all();
  mpz_set_ui(f,25);
  int j=0,te,ar=mpz_get_ui(c),success=0;
  mpz_t W[ar],i[ar],a[ar];
  char *V,*I,*w;

  mpz_powm(T,T,e,n);
  // while(j<25)
  //   mpz_init(W[j++]);
  // j=0;
  while(mpz_cmp_ui(c,j)>0){
    mpz_init(i[j]);
    mpz_init(a[j]);

    PRP(i[j],k1,j);
    PRF(a[j],k2,j);
    mpz_mod(i[j],i[j],f);
    mpz_mod(a[j],a[j],f);
    // gmp_printf("%Zd\n",)
    V=mpz_get_str (NULL,10,v);          // compute W[] for each block
    I=mpz_get_str (NULL,10,i[j]);
    w=(char *) malloc(1+strlen(V)+strlen(I));
    strcpy(w,V);
    strcat(w,I);      //concatenate'

    te=mpz_get_ui(i[j]);
    // cout<<te<<"\t"<<w<<endl;
    mpz_init(W[te]);
    mpz_set_str(W[te],w,10);
    // mpz_set(W[te],temp);
    free(V);
    free(I);
    free(w);

    hash_func(W[te],temp);         // modify T
    mpz_powm(temp,temp,a[j],n);
    mpz_invert(temp,temp,n);
    mpz_mul(T,T,temp);
    mpz_mod(T,T,n);

    j++;
  }
  //
  gmp_printf("T - %Zd\n",T);
  mpz_powm(T,T,s,n);
  HASH(T,hashed_val);
  gmp_printf("hashed val - %Zd\nrho - %Zd\n",hashed_val,rho);
  if(mpz_cmp(hashed_val,rho)==0)
    success=1;
  cout<<endl<<success;
  // return success;
  return 0;
}

void read_all(){
  fstream key_file;
  string word,temp,filename,n_keygen,v_keygen,e_keygen,k1_gen,k2_gen,s_gen,c_gen,g_gen,T_gen,rho_gen;
  // read values from keygen and file_blocks
  filename = "../outputs/key_gen_out.txt";
  key_file.open(filename.c_str());
  int i=1;
  while (key_file >> word)
  {
      if(i%12==0)
        v_keygen=word;
      else if(i%9==0)
        temp=word;
      else if(i%6==0)
        e_keygen=word;
      else if(i%3==0)
        n_keygen=word;
      i++;
  }
  key_file.close();
  filename = "../outputs/gen_chal_out.txt";
  key_file.open(filename.c_str());
  i=1;
  while (key_file >> word)
  {
    // cout<<word;
      if(i%18==0)
        temp=word;
      else if(i%15==0)
        g_gen=word;
      else if(i%12==0)
        c_gen=word;
      else if(i%9==0)
        s_gen=word;
      else if(i%6==0)
        k2_gen=word;
      else if(i%3==0)
        k1_gen=word;
      i++;
  }
  key_file.close();
  filename = "../outputs/gen_proof_out.txt";
  key_file.open(filename.c_str());
  i=1;
  while (key_file >> word)
  {
    // cout<<word;
      if(i%4==0)
        rho_gen=word;
      else if(i%2==0)
        T_gen=word;
      i++;
  }
  mpz_set_str (n,n_keygen.c_str(),10);
  // cout<<n_keygen<<endl;
  mpz_set_str (v,v_keygen.c_str(),10);
  mpz_set_str (e,e_keygen.c_str(),10);
  mpz_set_str (k1,k1_gen.c_str(),10);
  mpz_set_str (k2,k2_gen.c_str(),10);
  mpz_set_str (c,c_gen.c_str(),10);
  mpz_set_str (s,s_gen.c_str(),10);
  mpz_set_str (g,g_gen.c_str(),10);
  mpz_set_str (T,T_gen.c_str(),10);
  mpz_set_str (rho,rho_gen.c_str(),10);
  // gmp_printf("\nn - %Zd\nv - %Zd\ne - %Zd\nk1 - %Zd\nk2 - %Zd\nc - %Zd\ng - %Zd\nT - %Zd\nrho - %Zd",n,v,e,k1,k2,c,g,T,rho);
}
