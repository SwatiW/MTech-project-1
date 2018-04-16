void PRF(mpz_t a,mpz_t keytemp,int j){
  mpz_t temp,r;
  mpz_inits(temp,r,NULL);
  string te=to_string(j);
  const char *data=te.c_str();
  char *key;
  //itoa(j,data,10);
  int i;
  unsigned char *hash;
  unsigned int hashlen;
  key=mpz_get_str(NULL,10,keytemp);
  hash=HMAC(EVP_sha1(),key,strlen(key),(unsigned char*)data,strlen(data),NULL,&hashlen);
   // print_hex(hash,hashlen);

  for (i = 0; i < hashlen; i++){
    if((int)hash[i]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(a,a,r);
    mpz_add_ui(a,a,(int)hash[i]);
  }
}
/*
    char key[] = "012345678";

    char data[] = "hello world";
    unsigned char* digest;

    digest = HMAC(EVP_sha1(), key, strlen(key), (unsigned char*)data, strlen(data), NULL, NULL);

    char mdString[20];
    for(int i = 0; i < 20; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    printf("HMAC digest: %s\n", mdString);
*/
