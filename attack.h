#include <cstring>
#include <iostream>
#include <stdio.h>

using namespace std;

class Cipher
{

public:
    int Decrypt(unsigned char in[], unsigned int, unsigned char[]);
};

unsigned char ourSecretIv[16] = {0xcc, 0x0f, 0xa6, 0xa4, 0x7b, 0x39, 0x90, 0x72, 0xfb, 0x79, 0xf3, 0x14, 0x28, 0x4a, 0xed, 0x62};
