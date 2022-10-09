#include<stdio.h>
int swap(int* a, int* b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int swap2(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main()
{
    int a = 3;
    int b = 5;
    printf("%d \n", ~a);
    printf("Avant de swap : a = %d, b = %d \n", a, b);
    swap(&a, &b);
    printf("Après swap : a = %d, b = %d \n", a, b);
    swap2(&a, &b);
    printf("Après swap2 : a = %d, b = %d \n", a, b);
}