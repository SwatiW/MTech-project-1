//get (rho,T) from the service provider

#include<iostream>
#include<gmp.h>
#include<time.h>

int main(){

  mpz_t temp;
  mpz_inits(temp,NULL);
  int j=0,ar=mpz_get_ui(c);
  int i[ar],a[ar],W[ar],success=0;
  char *V,*I,*w;

  mpz_powm(T,T,e,n);

  while(mpz_cmp_ui(c,j)>0){
    i[j]=PRP(k1,j);                     // compute indices (aes)
    a[j]=PRF(k2,j);

    V=mpz_get_str (NULL,10,v);          // compute W[] for each block
    I=mpz_get_str (NULL,10,i[j]);
    w=(char *) malloc(1+strlen(V)+strlen(I));
    strcpy(w,V);
    strcat(w,I);      //concatenate
    mpz_set_str(W[i[j]],w,10);
    free(V);
    free(I);
    free(w);

    mpz_set(temp,hash(W[i[j]]));         // modify T
    mpz_powm(temp,temp,a[j],n);
    mpz_invert(temp,temp,n);
    mpz_mul(T,T,temp);
    mpz_mod(T,T,n);

    j++;
  }

  mpz_powm(T,T,s,n);
  if(mpz_cmp(HASH(T),rho)==0)
    success=1;

  // return success;
  return 0;
}
