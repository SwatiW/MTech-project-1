
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
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;
  cout<<"plaintext"<<endl;
cout<<plaintext<<endl;cout<<ciphertext<<endl;

  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}
void PRP(mpz_t store,mpz_t ke,int j,mpz_t iv_temp)
{
  mpz_t r;
  mpz_inits(r,NULL);
  int k;
  char *key = mpz_get_str(NULL,10,ke);

  char *iv = mpz_get_str(NULL,10,iv_temp);
  // cout<<"iv- "<<iv<<endl;
  string s=to_string(j);
  const char *plaintext =s.c_str();

  unsigned char ciphertext[128];

  int ciphertext_len;
  gmp_printf("%Zd %Zd\n",ke,iv_temp);
  cout<<j<<endl;

  ciphertext_len = encrypt ((unsigned char *)plaintext, strlen ((char *)plaintext), (unsigned char *)key,(unsigned char *)iv,ciphertext);
  // cout<<ciphertext<<endl;
  for (k = 0;k < ciphertext_len; k++){
    if((int)ciphertext[k]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(store,store,r);
    mpz_add_ui(store,store,(int)ciphertext[k]);
  }
  // gmp_printf("%Zd\n",store);
}
