#include<stdio.h>
#include<gmp.h>
#include<gmpxx.h>
#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
using namespace std;
mpz_t n;
void read_n();

int main()
{
    FILE *fp=fopen("../outputs/t1.txt", "r");
    char ch;
    vector<string> blocks_str;
    // vector<mpz_t> blocks;

    vector<string> :: iterator itr;
    string str,s;                                                 //to strore temp read file contents
    mpz_t F,f,b_size,temp;
    mpz_inits(F,f,b_size,temp,n,NULL);
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

    // gmp_printf("b_size -> %Zd\nF -> %Zd\nf -> %Zd\n",b_size,F,f);
    mpz_t blocks[mpz_get_ui(f)] ;
    for (i = 0; i < mpz_get_ui(f); i++) {
      mpz_init(blocks[i]);
    }
    read_n();
    // gmp_printf("%Zd\n",n);
    i=0;
    char *cstr;
    while(i!=str.length()){
      if(mpz_cmp_ui(b_size,s.length())==0){
        cstr=(char *) malloc(1+s.length());
        strcpy(cstr,s.c_str());
        mpz_set_str(temp,cstr,10);            // needs c style char string , not string
        mpz_set(blocks[t1],temp);
        mpz_mod(blocks[t1],blocks[t1],n);
        t1++;
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
      mpz_set(blocks[t1],temp);
      mpz_mod(blocks[t1],blocks[t1],n);
      t1++;
      s.clear();
    }
    // cout<<"index\tblock\n";
    for (i = 0; i < mpz_get_ui(f); i++) {
      // cout<<i<<"\t";
      gmp_printf("%d %Zd\n",i,blocks[i]);
    }

    fclose(fp);                             // closing the file pointer

    return 0;
}


void read_n(){

  fstream key_file;
  string word,filename,n_keygen;
  // read values from keygen and file_blocks
  filename = "../outputs/key_gen_out.txt";
  key_file.open(filename.c_str());
  int i=1;
  while (key_file >> word)
  {
      if(i%3==0 && i%6!=0 && i%9!=0 && i%12!=0 && i%15!=0)
        n_keygen=word;
      i++;
  }
  mpz_set_str (n,n_keygen.c_str(),10);
}
