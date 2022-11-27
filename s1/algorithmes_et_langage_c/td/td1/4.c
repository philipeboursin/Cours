#include<stdio.h>

void print_bits(unsigned int a)
{
    for (int i = 0; i < 32; i++)
    {
        printf("%d", (a >> i) & 0x1);
    }
    printf("\n");
}

int reverse(unsigned int a)
{
    unsigned int m11 = 0b00000000111111110000000011111111;
    unsigned int m12 = 0b11111111000000001111111100000000;
    unsigned int m21 = 0b00001111000011110000111100001111;
    unsigned int m22 = 0b11110000111100001111000011110000;
    unsigned int m31 = 0b00110011001100110011001100110011;
    unsigned int m32 = 0b11001100110011001100110011001100;
    unsigned int m41 = 0b01010101010101010101010101010101;
    unsigned int m42 = 0b10101010101010101010101010101010;
    a = (a << 16) ^ (a >> 16);
    a = ((a & m11) << 8) ^ ((a & m12) >> 8);
    a = ((a & m21) << 4) ^ ((a & m22) >> 4);
    a = ((a & m31) << 2) ^ ((a & m32) >> 2);
    a = ((a & m41) << 1) ^ ((a & m42) >> 1);
    return a;
}

int main()
{
    unsigned int a = 135283237;
    printf("a : ");
    print_bits(a);
    unsigned int b = a << (8*sizeof(unsigned int) - 1);
    printf("a après rotation : ");
    print_bits((a >> 1) ^ b);
    printf("a après inversion : ");
    print_bits(reverse(a));
}
