
void hash_func(mpz_t w,mpz_t hash_val){
  string msg;
  mpz_t temp,r;
  mpz_inits(temp,r,NULL);
  mpz_set(temp,w);
  int r_int,i;

  while(mpz_cmp_ui(temp,0)!=0){
    mpz_fdiv_qr_ui(temp,r,temp,100);
    r_int=mpz_get_ui(r);
    // cout<<r_int<<" - ";
    msg+=(char)r_int;
  }
  char *msg_to_hash;
  // cout<<"msg in c string => "<<msg<<endl;
  msg_to_hash=(char *) malloc(1+msg.length());
  strcpy(msg_to_hash,msg.c_str());
  unsigned char md[16];
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx,msg_to_hash,strlen(msg_to_hash));
  MD5_Final(md,&ctx);
  for (i = 0; i < sizeof(md); i++){
    if((int)md[i]>=100)
      mpz_set_ui(r,1000);
    else
      mpz_set_ui(r,100);
    mpz_mul(hash_val,hash_val,r);
    mpz_add_ui(hash_val,hash_val,(int)md[i]);
  }
  // gmp_printf("%Zd\n%Zd\n",w,hash_val);
}
