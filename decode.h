#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <string.h>

#include "types.h"




typedef struct _DecodeInfo
{
    
    /* Secret File Info */
    char *secret_fname;
    FILE *fptr_secret;
    int ext_size;   
   // char extn_secret_file[4];
   // char secret_data[8];
    unsigned long secret_file_size;

    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

    //Magic string
    int magic_string_size;      
    char magic_string[20];

}DecodeInfo;


Status decoding(DecodeInfo *decInfo);
unsigned int decode_lsb_to_int(DecodeInfo *decInfo);
unsigned char decode_lsb_to_byte(DecodeInfo *decInfo);


#endif







