#include<stdio.h>
#include<gmp.h>
#include<gmpxx.h>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int main()
{
    FILE *fp=fopen("t1.txt", "r");;
    char ch;
    vector<string> blocks_str;
    // vector<mpz_t> blocks;

    vector<string> :: iterator itr;
    string str,s;                                                 //to strore temp read file contents
    mpz_t F,f,b_size,temp;
    mpz_inits(F,f,b_size,temp,NULL);
    mpz_set_ui(b_size,8);           // size of each block
    int i=0,t=0,t1=0;

    fseek(fp, 0, SEEK_END);

    fseek(fp, 0, SEEK_SET);
    while((ch=getc(fp))!=EOF){
      t=(int) ch;
      str+=to_string(t);
    }

    mpz_set_ui(F,str.length());
    mpz_cdiv_q(f,F,b_size);                      // no of total blocks

    gmp_printf("b_size -> %Zd\nF -> %Zd\nf -> %Zd\n",b_size,F,f);
    mpz_t blocks[mpz_get_ui(f)] ;
    for (i = 0; i < mpz_get_ui(f); i++) {
      mpz_init(blocks[i]);
    }

    i=0;
    char *cstr;
    while(i!=str.length()){
      if(mpz_cmp_ui(b_size,s.length())==0){
        cstr=(char *) malloc(1+s.length());
        strcpy(cstr,s.c_str());
        mpz_set_str(temp,cstr,10);            // needs c style char string , not string
        mpz_set(blocks[t1++],temp);
        s.clear();
      }
      s+=str[i];
      i++;
    }
    if(s.length()!=0){
      while(mpz_cmp_ui(b_size,s.length())!=0)
        s+='0';
      cstr=(char *) malloc(1+s.length());
      strcpy(cstr,s.c_str());
      mpz_set_str(temp,cstr,10);            // needs c style char string , not string
      mpz_set(blocks[t1++],temp);
      s.clear();
    }

    for (i = 0; i < mpz_get_ui(f); i++) {
      cout<<i<<"\t";
      gmp_printf("%Zd\n",blocks[i]);
    }

    fclose(fp);                             // closing the file pointer

    return 0;
}
