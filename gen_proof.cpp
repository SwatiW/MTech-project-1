#include<iostream>
#include<gmp.h>
#include<time.h>
using namespace std;

int main(){
  mpz_t T,temp,ex,rho;
  int j=0,itr,i[mpz_get_ui(c)],a[mpz_get_ui(c)];
  mpz_inits(T,temp,ex,rho,NULL);
  // for (itr = 0; itr < mpz_get_ui(c); itr++) {
  //   mpz_inits(i[itr],a[itr],NULL);
  // }

  while(mpz_cmp_ui(c,j)>0){
    i[j]=PRP(k1,j);                     //compute indices (aes)
    a[j]=PRF(k2,j);                     //compute coefficients (hmac)
    j++;
  }

  j=0;
  mpz_set_ui(T,1);
  while(mpz_cmp_ui(c,j)>0){
    mpz_powm(temp,tag[i[j]],a[j],n);
    mpz_mul_ui(T,T,temp);                              //calculate T
    mpz_mod(T,T,n);

    mpz_mul_ui(temp,b[j],a[j]);
    mpz_add(ex,ex,temp);
    mpz_mod(ex,ex,n);
    j++;
  }

  mpz_powm(temp,gs,ex,n);
  mpz_set(rho,HASH(temp));

  //  (T,rho) is the proof generated

  return 0;
}
