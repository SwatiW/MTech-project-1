//tag generation for each file block
//  W(i)= v || i
//  T(i,b(i))= ( h(W(i)) * g^i )^d mod n

// v size = 128 bits

#include<gmp.h>
#include<iostream>
#include<time.h>

int main(){

  //get the secret v from keygen

  mpz_t f,*W,i;
  mpz_inits(t,i,NULL);
  W=(mpz_t *) malloc(f*sizeof(mpz_t));

  for(mpz_set_ui(i,0),mpz_cmp_ui(i,f)<0;mpz_set(i,i+1)){
    W[i]=generate_w(v,i);
    generate_tag(i,W[i]);
  }
  return 0;
}



//  W(i)= v || i  --concatenations
mpz_t generate_w(mpz_t v,mpz_t i){
  mpz_t W;
  mpz_inits(W,NULL);
  char *V,*I,*w;

  V=mpz_get_str (NULL,10,v);   //Convert v to a string of digits in base 10.
  I=mpz_get_str (NULL,10,i);
  w=(char *) malloc(1+strlen(V)+strlen(I));
  strcpy(w,V);
  strcat(w,I);      //concatenate

  mpz_set_str(W[i],w,10); //Set the value of W[i] from w, a null-terminated C string in base base. White space is allowed
                          //in the string, and is simply ignored.
  gmp_printf("%Zd\n%Zd\n%Zd\n",v,i,W[i]);

  free(V);
  free(I);
  free(w);

  //return W(i)
}


mpz_t generate_tag(mpz_t i,mpz_t W){
  mpz_t G,T;
  mpz_init(G);

  //  G = g^i
  mpz_powm (G,g,i,n);

  // hash = h(W(i))


  //  T(i,b(i))= ( hash * G )^d mod n
  mpz_mul(T,hash,G);
  mpz_powm(T,T,d,n);

}
