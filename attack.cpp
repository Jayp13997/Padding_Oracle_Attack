#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "attack.h"
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("please provide ciphertext file\n");
        exit(0);
    }
    
    unsigned char ciphertext[160];
    ifstream infile;
    infile.open(argv[1]);
    infile.read((char *)ciphertext, 160);
    
    unsigned char plaintext[160];
    memset(plaintext, 0, 160);

    unsigned char plaintext_padded[160];
    memset(plaintext_padded, 0, 160);

    unsigned char blocks[10][16];

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 16; j++){
            blocks[i][j] = ciphertext[(i * 16) + j];
        }
    }

    for(int block_num = 9; block_num >= 0; block_num--){

        
        if(block_num == 0){
            unsigned char test_cipher[16];
            for(int i = 0; i < 16; i++){
                test_cipher[i] = ciphertext[i]; 
            }

            unsigned char prev_block[16];
            for(int i = 0; i < 16; i++){
                prev_block[i] = ourSecretIv[i];
            }

            unsigned char plaintext_block[16];
            memset(plaintext_block, 0, 16);

            for(int i = 0; i < 16; i++){

                unsigned char padding[16];
                memset(padding, 0, 16);

                for(int j = 0; j < i; j++){
                    padding[15-j] = i+1;
                }

                for(int j = 0; j < i; j++){
                    prev_block[15-j] = padding[15-j] ^ plaintext_block[15-j] ^ ourSecretIv[15-j];
                }
                
                unsigned char ignore_byte = ourSecretIv[15-i];

                for(unsigned char byte = 0; byte < 256; byte++){
                    if(byte == ignore_byte && i == 0){
                        continue;
                    }

                    prev_block[15-i] = byte;

                    Cipher cipher_test;
                    int result = cipher_test.Decrypt(test_cipher, 16, prev_block);
                    if(result == 0){
                        plaintext_block[15-i] = byte ^ (i+1) ^ ourSecretIv[15-i];
                        break;
                    }
                }
            }

            for(int k = 0; k < 16; k++){
                plaintext_padded[k] = plaintext_block[k];
            }

        }else{

            unsigned char test_cipher[32];
            for(int i = 0; i < 32; i++){
                test_cipher[i] = ciphertext[((block_num - 1) * 16) + i];
            }

            unsigned char prev_block[16];
            for(int i = 0; i < 16; i++){
                prev_block[i] = test_cipher[i];
            }

            unsigned char plaintext_block[16];
            memset(plaintext_block, 0, 16);


            for(int i = 0; i < 16; i++){

                unsigned char padding[16];
                memset(padding, 0, 16);

                for(int j = 0; j < i; j++){
                    padding[15-j] = i+1;
                }

                for(int j = 0; j < i; j++){
                    test_cipher[15-j] = padding[15-j] ^ plaintext_block[15-j] ^ prev_block[15-j];
                }

                unsigned char ignore_byte = blocks[block_num-1][15-i];

                for(unsigned char byte = 0; byte < 256; byte++){
                    if(byte == ignore_byte && i == 0){
                        continue;
                    }

                    test_cipher[15-i] = byte;

                    Cipher cipher_test;
                    int result = cipher_test.Decrypt(test_cipher, 32, prev_block);   

                    if(result == 0){
                        plaintext_block[15-i] = byte ^ (i+1) ^ blocks[block_num-1][15-i];
                        break;
                    }     
                }
            }

            for(int k = 0; k < 16; k++){
                plaintext_padded[(block_num * 16) + k] = plaintext_block[k];
            }
        }
    }

    unsigned char padded_num = plaintext_padded[159];

    for(int i = 0; i < 160 - (int)padded_num; i++){
        plaintext[i] = plaintext_padded[i];
    }
    printf("%s\n", plaintext);
    
    return 0;
}

