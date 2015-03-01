# include "dict.h"
# include <stdio.h>

int *insert_lookup_1_svc(dictTuple *inp, struct svc_req *rqstp)
{
 static int status=0;
 FILE* file_ptr;
 char buffer[200];
 char* token;
 const char delimiter[1]=",";
 int input_len;
 int row=0;
 //Meaning does not exist in the input
 //So we search for the meaning
 input_len=strlen(inp->meaning);
 if(input_len==0)
 {
  file_ptr=fopen("Dictionary_File.txt","r");
  if(file_ptr==NULL)
  {
   fclose(file_ptr);
   status=-1;
   return(&status);
  }
  while(fgets(buffer,sizeof(buffer),file_ptr)!=NULL)
  {
   row=row+1;
   token=strtok(buffer,delimiter);
   if(strcmp(inp->word,token)==0)
   {
     strcpy(inp->meaning,token);
     fclose(file_ptr);
     //return row number where meaning was found
     status=row;
     return(&status);
   }   
  }
  //If program control comes here then word does not exist
  //in the dictinary
  status=0;
  fclose(file_ptr);
  return(&status); 
  printf("%d\n",input_len); 
 }
 else
 {
  //If meaning found in input then write it to the
  //dictionary file
  file_ptr=fopen("Dictionary_File.txt","a+");
  if(file_ptr==NULL)
  {
   fclose(file_ptr);
   status=-1;
   return(&status);
  }
  fprintf(file_ptr,"%s,%s\n",inp->word,inp->meaning);
  fflush(file_ptr);
  fclose(file_ptr);
  status=0;
  return(&status);
 }
 return(&status);
}
