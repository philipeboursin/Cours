#include<stdio.h>
#include<stdlib.h>

unsigned int hamming_weight(unsigned int v)
{
    unsigned int m11 = 0b01010101010101010101010101010101;
    unsigned int m12 = 0b10101010101010101010101010101010;
    unsigned int m21 = 0b00110011001100110011001100110011;
    unsigned int m22 = 0b11001100110011001100110011001100;
    unsigned int m31 = 0b00001111000011110000111100001111;
    unsigned int m32 = 0b11110000111100001111000011110000;
    unsigned int m41 = 0b00000000111111110000000011111111;
    unsigned int m42 = 0b11111111000000001111111100000000;
    unsigned int m51 = 0b00000000000000001111111111111111;
    unsigned int m52 = 0b11111111111111110000000000000000;
    v = ((v & m11) + ((v & m12) >> 1));
    v = ((v & m21) + ((v & m22) >> 2));
    v = ((v & m31) + ((v & m32) >> 4));
    v = ((v & m41) + ((v & m42) >> 8));
    v = ((v & m51) + ((v & m52) >> 16));
    return v;
}

unsigned int hamming_weight_bis(unsigned int v)
{
    int i = 0;
    while (v != 0)
    {
        i++;
        v = v & (v - 1);
    }
    return i;
}

int main(int n, char** argv)
{
    unsigned int v = atoi(argv[1]);
    // unsigned int v = 0b10100100010110100101001010;
    printf("%d\n", hamming_weight_bis(v));
}