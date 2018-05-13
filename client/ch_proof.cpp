#include<bits/stdc++.h>
#include<gmp.h>
#include<openssl/md5.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include<openssl/conf.h>
#include<openssl/err.h>
#include<openssl/aes.h>

using namespace std;

#include "../random_num.cpp"
#include "../crypto_funcs/sha1.cpp"

#include "../crypto_funcs/simple_hash.cpp"
#include "../crypto_funcs/hmac.cpp"
void read_all();
mpz_t c,k1,k2,s,T,rho,n,g,e,v,gs,iv_temp;

int main(){
  mpz_t f,hashed,hashed_val;
  mpz_inits(c,k1,k2,s,T,rho,n,g,gs,e,v,iv_temp,f,hashed,hashed_val,NULL);
  int j,temp,in,te,success=0;
  char *V,*I,*w;
  read_all();
  // gmp_printf("c-%Zd\nk1-%Zd\nk2-%Zd\ns-%Zd\nT-%Zd\nrho-%Zd\nn-%Zd\ng-%Zd\ngs-%Zd\ne-%Zd\nv-%Zd\n",c,k1,k2,s,T,rho,n,g,gs,e,v);

  in=mpz_get_ui(c)+1;
  mpz_t W[in],i[in],a[in];
  mpz_set_ui(f,25);
  mpz_powm(T,T,e,n);

  // for(j=1;j<in;j++){
  //   mpz_inits(i[j],a[j],NULL);
    fstream file;
    string word,tempi,filename="../outputs/PRP_out.txt";
    file.open(filename.c_str());
    temp=1;
    j=1;
    while (file >> word) {

      if(temp==6){
        mpz_inits(i[j],a[j],NULL);
        mpz_set_str (i[j],word.c_str(),10);
        temp=1;
        PRF(a[j],k2,j);
        mpz_mod(a[j],a[j],f);

        V=mpz_get_str (NULL,10,v);          // compute W[] for each block
        I=mpz_get_str (NULL,10,i[j]);
        w=(char *) malloc(1+strlen(V)+strlen(I));
        strcpy(w,V);
        strcat(w,I);      //concatenate
        // gmp_printf("j - %d\t i - %Zd\t a - %Zd\n",j,i[j],a[j]);

        te=mpz_get_ui(i[j]);
        mpz_init(W[te]);
        mpz_set_str(W[te],w,10);
         // gmp_printf("i - %d\t%Zd\n",te,W[te]);
        hash_func(W[te],hashed);
        mpz_powm(hashed,hashed,a[j],n);
        mpz_invert(hashed,hashed,n);
        mpz_mul(T,T,hashed);
        mpz_mod(T,T,n);

        j++;
      }
      else
        temp++;
    }

    mpz_powm(T,T,s,n);
    HASH(T,hashed_val);
    // gmp_printf("hashed val - %Zd\nrho - %Zd\n",hashed_val,rho);
    if(mpz_cmp(hashed_val,rho)==0)
      success=1;
    // cout<<"success - "<<success<<endl;

  return 0;
}


void read_all(){
  fstream read_file;
  string filename,word,c_te,k1_te,k2_te,s_te,T_te,rho_te,n_te,g_te,e_te,v_te,gs_te,iv_te;
  //read keys
  filename = "../outputs/key_gen_out.txt";
  read_file.open(filename.c_str());
  int i;
  i=1;
  while(read_file >> word){
    if(i==3)
      n_te=word;
    else if(i==6)
      e_te=word;
    else if(i==12)
      v_te=word;
    else if(i==15)
      iv_te=word;
    i++;
  }
  read_file.close();
  //read challenge
  filename = "../outputs/gen_chal_out.txt";
  read_file.open(filename.c_str());
  i=1;
  while(read_file >> word){
    if(i==3)
      k1_te=word;
    else if(i==6)
      k2_te=word;
    else if(i==9)
      s_te=word;
    else if(i==12)
      c_te=word;
    else if(i==15)
      g_te=word;
    else if(i==18)
      gs_te=word;
    i++;
  }
  read_file.close();
  //read proof
  filename = "../outputs/gen_proof_out.txt";
  read_file.open(filename.c_str());
  i=1;
  while(read_file >> word){
    if(i==3)
      T_te=word;
    else if(i==6)
      rho_te=word;
    i++;
  }
  read_file.close();

  mpz_set_str (s,s_te.c_str(),10);
  mpz_set_str (c,c_te.c_str(),10);
  mpz_set_str (k1,k1_te.c_str(),10);
  mpz_set_str (k2,k2_te.c_str(),10);
  mpz_set_str (gs,gs_te.c_str(),10);
  mpz_set_str (g,g_te.c_str(),10);
  mpz_set_str (v,v_te.c_str(),10);
  mpz_set_str (iv_temp,iv_te.c_str(),10);
  mpz_set_str (e,e_te.c_str(),10);
  mpz_set_str (n,n_te.c_str(),10);
  mpz_set_str (T,T_te.c_str(),10);
  mpz_set_str (rho,rho_te.c_str(),10);
  // gmp_printf("T - %Zd\nrho - %Zd\n",T,rho);
}
