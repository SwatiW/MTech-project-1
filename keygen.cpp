// generating the rsa modulus n and keys
// n -> modulus
// n = p*q
// phi -> totient function
// g -> generator
// v -> random secret
// e -> public key -> pk=(N,g,e)
// d -> private key -> sk=(d,v)

#include<iostream>
#include<gmp.h>
#include<time.h>
#include "random_num.cpp"

using namespace std;

int main()
{
  mpz_t p,q,pd,qd,n,phi,_p,_q,e,d,v,gcd,r_max,iv_temp;
  mpz_inits(p,q,pd,qd,n,phi,_p,_q,e,d,v,gcd,r_max,iv_temp,NULL);
  // set<mpz_t> mul_grp;
  // p and q -> primes -> size 512 bits
  unsigned long int seed;
  gmp_randstate_t r_state;
  seed = time(NULL);
  gmp_randinit_default (r_state);
  gmp_randseed_ui(r_state, seed);

  mpz_set_ui(r_max,0);
  gen_random_no(1,512,r_max,p,r_state);
  gen_random_no(1,512,r_max,q,r_state);
  gen_random_no(1,128,r_max,iv_temp,r_state);
  mpz_nextprime(pd,p);
  mpz_nextprime(qd,q);
  mpz_mul_ui(p,pd,2);
  mpz_mul_ui(q,qd,2);
  mpz_add_ui(p,p,1);
  mpz_add_ui(q,q,1);
  // n=p*q -> size 1024 bits
  mpz_mul(n,p,q);

  // phi= (p-1)(q-1) = _p * _q
  mpz_sub_ui(_p,p,1);
  mpz_sub_ui(_q,q,1);
  mpz_mul(phi,_p,_q);

  // e ->1024 bits

  do{
    gen_random_no(1,1024,r_max,e,r_state);
    mpz_gcd(gcd,e,phi);
  }while(mpz_cmp_ui(e,1)<1 || mpz_cmp(e,phi)>1 || mpz_cmp_ui(gcd,1)!=0 );


  // d -> 1024 bits
  mpz_invert(d,e,phi);

  // mpz_urandomb(v,r_state,128);
  gen_random_no(1,128,r_max,v,r_state);
  // gmp_printf("p -> %Zd\nq -> %Zd\nn -> %Zd\ne -> %Zd\nd -> %Zd\nv -> %Zd\n",p,q,n,e,d,v);

  gmp_printf("n -> %Zd\ne -> %Zd\nd -> %Zd\nv -> %Zd\niv_temp -> %Zd\n",n,e,d,v,iv_temp);


  return 0;
}



//RSA key generation

// Generate two large random (and distinct) primes p and q, each roughly the same size.
// 2. Compute n = pq and φ = (p − 1)(q − 1).
// 3. Select a random integer e, 1 < e < φ, such that gcd(e, φ) = 1.
// 4. Use the extended Euclidean algorithm  to compute the unique integer d, 1 < d < φ, such that ed ≡ 1 (mod φ).
// 5. A’s public key is (n, e); A’s private key is d.
