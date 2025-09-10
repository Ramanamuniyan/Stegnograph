#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include <stdlib.h>

unsigned char decode_lsb_to_byte(DecodeInfo *decInfo)
{
   unsigned char buf[8];   
    fread(buf,8,1,decInfo->fptr_stego_image);
  unsigned  char size=0;
  
    for(int i=0;i<8;i++)
    {   
        size |= (buf[i] & 1)  << (7-i); 
    }
   return size;
}


unsigned int decode_lsb_to_int(DecodeInfo *decInfo)
{
    unsigned  char buf[32];
    fread(buf,32,1,decInfo->fptr_stego_image );
      unsigned  int size=0;
   //printf("%c",buf[0]);
    for(int i=0;i<32;i++)
    {    
        size |= (buf[i] & 1)  << (31-i);   
    }
 
    return size;
}


Status decoding(DecodeInfo *decInfo)
{

    decInfo->ext_size = decode_lsb_to_int(decInfo); //getting exten size

    unsigned char buff_ext[4];
    for(int i=0;i<decInfo->ext_size;i++)
    {
        buff_ext[i]=decode_lsb_to_byte(decInfo);
    }

   // 

    decInfo->secret_fname = malloc(strlen("decode_file") + strlen(buff_ext) + 1);
    strcpy(decInfo->secret_fname, "decode_file");
    strcat(decInfo->secret_fname, buff_ext);

    decInfo->secret_file_size = decode_lsb_to_int(decInfo); //getting exten size

   // printf("%lu",decInfo->secret_file_size );
    FILE *fptr=fopen(decInfo->secret_fname,"wb");

    if(fptr ==NULL)
    {
        perror("");
        return e_failure;
    }
    

    for(int i=0;i<decInfo->secret_file_size;i++)
    {
        unsigned char buff;

        buff=decode_lsb_to_byte(decInfo);

        fwrite(&buff,1,1,fptr);
    }




    return e_success;
}