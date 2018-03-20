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
int gen_random_no(int out,int bit_cnt,mpz_t max_no,mpz_t rand_no);

using namespace std;

int main()
{
  mpz_t p,q,n,phi,_p,_q,e,d,v,gcd,r_max;
  mpz_inits(p,q,n,phi,_p,_q,e,d,v,gcd,r_max,NULL);

  // p and q -> primes -> size 512 bits
  mpz_set_ui(r_max,0);
  gen_random_no(1,512,r_max,p);
  gen_random_no(1,512,r_max,q);

  mpz_nextprime(p,p);
  mpz_nextprime(q,q);

  // n=p*q -> size 1024 bits
  mpz_mul(n,p,q);

  // phi= (p-1)(q-1) = _p * _q
  mpz_sub_ui(_p,p,1);
  mpz_sub_ui(_q,q,1);
  mpz_mul(phi,_p,_q);

  // e ->1024 bits

  do{
    gen_random_no(1,1024,r_max,e);
    mpz_gcd(gcd,e,phi);
  }while(mpz_cmp_ui(e,1)<1 || mpz_cmp(e,phi)>1 || mpz_cmp_ui(gcd,1)!=0 );


  // d -> 1024 bits
  mpz_invert(d,e,phi);

  // mpz_urandomb(v,r_state,128);
  gen_random_no(1,128,r_max,v);
  gmp_printf("p -> %Zd\nq -> %Zd\nn -> %Zd\ne -> %Zd\nd -> %Zd\nv -> %Zd\n",p,q,n,e,d,v);

  return 0;
}



//RSA key generation

// Generate two large random (and distinct) primes p and q, each roughly the same size.
// 2. Compute n = pq and φ = (p − 1)(q − 1).
// 3. Select a random integer e, 1 < e < φ, such that gcd(e, φ) = 1.
// 4. Use the extended Euclidean algorithm  to compute the unique integer d, 1 < d < φ, such that ed ≡ 1 (mod φ).
// 5. A’s public key is (n, e); A’s private key is d.
