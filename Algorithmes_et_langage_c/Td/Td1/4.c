#include<stdio.h>

void print_bits(unsigned a)
{
    for (int i = 0; i < 32; i++)
    {
        printf("%d", (a >> i) & 0x1);
    }
    printf("\n");
}

int reverse(unsigned int a)
{
    unsigned int m11 = 0x00ff00ff;
    unsigned int m12 = m11 << 8;
    unsigned int m21 = 0x0f0f0f0f;
    unsigned int m22 = m21 << 4;
    unsigned int m31 = 858993459;
    unsigned int m32 = m31 << 2;
    unsigned int m41 = 1431655765;
    unsigned int m42 = m41 << 1;
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