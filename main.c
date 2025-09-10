#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include "string.h"

int main(int argc,char* argv[])
{

    if(argc < 2)
    {
        
        printf(RED"For Encoding : ./a.out -e <original.bmp_file> <secrect_file> <newfile.bmp>\n"RESET);
        printf(RED"For decoding : ./a.out -d <encoded.bmp_file> \n"RESET);

        return e_failure;
    }
   if(check_operation_type(argv)== e_encode)
   {
   
    if(argc < 4)
    {      
        printf(RED"For Encoding : ./a.out <.bmp_file> <secrect_file> <newfile.bmp>\n"RESET);
        return e_failure;
    }


    printf("You have chosed Encoding\n");

    EncodeInfo encInfo;  // structure 

    //puts(encInfo.src_image_fname);

    printf("Enter the magic string : ");
    scanf("%[^\n]",encInfo.magic_string);

      encInfo.magic_string_size= strlen(encInfo.magic_string);
   // printf("%d",encInfo.magic_string_size);


    if(read_and_validate_encode_args(argv, &encInfo))
   {
        puts("image shoul be .bmp");
        puts("Secrect file should have . extension");
        return e_failure;
   }

    else
    {
        encInfo.src_image_fname=argv[2];
        encInfo.secret_fname=argv[3];
    }

   
    
    

    
    if(argv[4]!=NULL)
    {
         if( strstr(argv[4],".bmp")==NULL)
         {
            puts("New file should be .bmp");
            return e_failure;
         }
         else
            encInfo.stego_image_fname=argv[4];

    }
    
    else  

    encInfo.stego_image_fname="stego.bmp";// if stego 


    


     // reading image capacity


   


  

     
    int ret =do_encoding(&encInfo);

    if(ret==e_success)
    puts("\033[1;32mEncoding is Done");

   

    else 
    puts(RED"Encoding is not Done"RESET);

   // printf("%d",encInfo.ext_size);



    return e_success;

   }

   else if (check_operation_type(argv) == e_decode)
   {


    DecodeInfo decInfo;
    printf("You have chosed Decoding\n");

    printf("Enter the magic string to decode :");
    char magic[20];
    scanf("%[^\n]",magic);

      

    if(argv[2]!= NULL && strstr(argv[2],".bmp")!= NULL)
    decInfo.stego_image_fname =argv[2];
    else
    {
    printf("Enter the encoded .bmp file:");

    //getc();
    char stego[20];
    scanf(" %[^\n]",stego);
        if(strstr(stego,".bmp")!= NULL)
        decInfo.stego_image_fname =stego;
        
        else
        {
            puts(RED"Enter valid stego file"RESET);
       return  e_failure;
        }

    }

    




    decInfo.fptr_stego_image=fopen(decInfo.stego_image_fname ,"r");

    puts("File opened");

    fseek(decInfo.fptr_stego_image,54,SEEK_SET);


    
    decInfo.magic_string_size = decode_lsb_to_int(&decInfo);   //get the magic strlen
   // printf("%d\n",decInfo.magic_string_size );

    unsigned char buff_magic[20];
    for(int i=0;i<decInfo.magic_string_size;i++)
    {
    buff_magic[i]=decode_lsb_to_byte(&decInfo);
    }
   // printf("%s",buff_magic);

   if(strcmp(buff_magic,magic)!=0)
   puts(RED"Magic string not match"RESET);
   else
   {
    puts("Magic string matched");
    puts("Started Decoding");


   if( decoding(&decInfo)==e_success)
   puts("\033[1;32mDecoding done\033[0m");
    else
    puts(RED"Decoding not done"RESET);


   }





        return e_success;

   }

   else if(check_operation_type(argv) == e_unsupported)
    printf("Enter correct argument\n");

   return e_failure;
}


