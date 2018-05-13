#include<bits/stdc++.h>
#include<gmp.h>
#include<openssl/md5.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include<openssl/conf.h>
#include<openssl/err.h>
using namespace std;

mpz_t c,ke,iv_temp,n;
void read_all();

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;
  int len,ciphertext_len;
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, NULL))
    handleErrors();

  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  EVP_CIPHER_CTX_free(ctx);
  return ciphertext_len;
}

int main()
{
  mpz_t r;
  mpz_inits(r,ke,iv_temp,NULL);
  read_all();
  // gmp_printf("c-%Zd\nk1-%Zd\niv_temp-%Zd\nn-%Zd\n",c,ke,iv_temp,n);

  int k,j,in=in=mpz_get_ui(c)+1;

  char *key = mpz_get_str(NULL,10,ke);
  char *iv = mpz_get_str(NULL,10,iv_temp);
  mpz_t i[in];

  for(j=1;j<in;j++){
    string s=to_string(j);
    const char *plaintext =s.c_str();

    unsigned char ciphertext[128];
    int ciphertext_len;

    ciphertext_len = encrypt ((unsigned char *)plaintext, strlen ((char *)plaintext), (unsigned char *)key,(unsigned char *)iv,ciphertext);

    mpz_inits(r,i[j],NULL);
    for (k = 0;k < ciphertext_len; k++){
      if((int)ciphertext[k]>=100)
        mpz_set_ui(r,1000);
      else
        mpz_set_ui(r,100);
      mpz_mul(i[j],i[j],r);
      mpz_add_ui(i[j],i[j],(int)ciphertext[k]);
    }
    mpz_mod_ui(i[j],i[j],25);
    gmp_printf("j - %d\t i - %Zd\n",j,i[j]);

  }
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
    else if(i==12)
      c_te=word;
    i++;
  }
  read_file.close();

  mpz_set_str (c,c_te.c_str(),10);
  mpz_set_str (ke,k1_te.c_str(),10);
  mpz_set_str (iv_temp,iv_te.c_str(),10);
  mpz_set_str (n,n_te.c_str(),10);
}
