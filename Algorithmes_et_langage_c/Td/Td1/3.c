#include<stdio.h>

int main()
{
    int a = 8;
    int i = 2;
    printf("%d / 2^%d = %d \n", a, i, a >> i); // division par 2^i
    a = 7;
    printf("%d mod 2^%d = %d \n", a, i, a ^ ((a >> i) << i)); // reste modulo 2^i
    printf("%d * 2^%d = %d \n", a, i, a << i); // multiplie par 2^i
    printf("%d * 17 = %d \n ", a, a + (a << 4)); // multiplie par 17
}