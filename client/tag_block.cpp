// tag generation for each file block
//  W(i)= v || i
//  T(i,b(i))= ( h(W(i)) * g^b[i] )^d mod n

// v size = 128 bits

#include<gmp.h>
#include<iostream>
#include<time.h>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<openssl/md5.h>
using namespace std;
#include "../crypto_funcs/simple_hash.cpp"


mpz_t n,v,d,g;
void read_n_v_d();
void generate_w(mpz_t i,mpz_t wgen);
void generate_tag(mpz_t tag_gen,mpz_t wgen,mpz_t block);

int main(){

  mpz_t f,j;
  mpz_inits(g,f,j,n,v,d,NULL);
  mpz_set_ui(f,25);
  mpz_t b[mpz_get_ui(f)] ;
  int i,k;
  mpz_t W[mpz_get_ui(f)],T[mpz_get_ui(f)];
  for (i = 0; i < mpz_get_ui(f); i++) {
    mpz_init(W[i]);
    mpz_init(T[i]);
    mpz_init(b[i]);
  }
  read_n_v_d();
  fstream block_file;
  string word,filename;
  filename = "../outputs/file_blocks_out.txt";
  block_file.open(filename.c_str());
  i=0;
  k=0;
  while(block_file >> word){
    if(i%2!=0){
      mpz_set_str(b[k],word.c_str(),10);
      k++;
    }
    i++;
  }

  i=0;
  while(mpz_cmp(f,j)>0){
    generate_w(j,W[i]);

    generate_tag(T[i],W[i],b[i]);       //compute coefficients (hmac)
    i++;
    mpz_add_ui(j,j,1);
  }
  i=0;
  gmp_printf("index\tblock\ttag\n");
  while(mpz_cmp_ui(f,i)>0){

    gmp_printf("%d\t%Zd\t%Zd\n",i,b[i],T[i]);
    i++;

  }
  return 0;
}

void read_n_v_d(){
  fstream key_file,block_file;
  string word,filename,n_keygen,v_keygen,d_keygen,g_keygen;
  // read values from keygen and file_blocks
  filename = "../outputs/key_gen_out.txt";
  key_file.open(filename.c_str());
  int i=1;
  while (key_file >> word)
  {
      if(i%12==0)
        v_keygen=word;
      else if(i%9==0)
        d_keygen=word;
      else if(i%6==0)
        g_keygen=word;
      else if(i%3==0)
        n_keygen=word;
      i++;
  }
  mpz_set_str (n,n_keygen.c_str(),10);
  mpz_set_str (g,g_keygen.c_str(),10);
  mpz_set_str (d,d_keygen.c_str(),10);
  mpz_set_str (v,v_keygen.c_str(),10);
}
//
//  W(i)= v || i  --concatenations
void generate_w(mpz_t i,mpz_t wgen){
  char *V,*I,*w;

  V=mpz_get_str (NULL,10,v);   //Convert v to a string of digits in base 10.
  I=mpz_get_str (NULL,10,i);
  w=(char *) malloc(1+strlen(V)+strlen(I));
  strcpy(w,V);
  strcat(w,I);      //concatenate

  mpz_set_str(wgen,w,10); //Set the value of W[i] from w, a null-terminated C string in base base. White space is allowed
                          //in the string, and is simply ignored.

  free(V);
  free(I);
  free(w);


}

// //  T(i,b(i))= ( h(W(i)) * g^b[i] )^d mod n
void generate_tag(mpz_t tag_gen,mpz_t wgen,mpz_t block){
  mpz_t G,temp;
  mpz_inits(G,temp,NULL);

  // G = g^b[i]
  mpz_powm (G,g,block,n);
  hash_func(wgen,temp);
  //
  // //  T(i,b(i))= ( temp * G )^d mod n
  mpz_mul(tag_gen,temp,G);
  mpz_powm(tag_gen,tag_gen,d,n);

}
