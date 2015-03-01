#include "dict.h"
#include <stdio.h>

int main (int argc, char **argv)
{
 CLIENT *cl;
 dictTuple in;
 int *status;
 
 if (argc==1)
 {
  printf("dictclient <word> <meaning> OR dictclient <word>");
  exit(1);
 } 

 cl = clnt_create("localhost",DICTIONARY,INSERT_LOOKUP_VERS,"tcp");
 if(cl==NULL)
 {
  printf("Connection Failed\n");
  exit(1);
 }
 else
 {
  printf("Connected to Server\n");
 }
 //Initialize the dictionary input variables
 in.word[0]=0;
 in.meaning[0]=0;
 //Copy the arguments to the input variables
 strcpy(in.word,argv[1]);
 printf("Word: %s\n", in.word);;
 if(argc==3)
 {
  strcpy(in.meaning,argv[2]);
 }
 //Call Dictionary RPC
 status=insert_lookup_1(&in,cl);
 if(*status==0 && argc==3)
 {
   printf("Added Meaning: %s\n",in.meaning);
 }
 else
 {
  if (*status>=1)
  {
   printf("Meaning Found on Line: %d\n",*status);
  }
  else if(*status==0)
  {
   printf("Word not found in dictionary\n");
  }
  else if(*status==-1)
  {
   printf("Dictionary file is not available\n");
  } 
 }
} 
  
