#include<stdio.h>
#include<stdlib.h>

int factorielle(int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
        res *= i;
    }
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Mauvais nombre d'arguments");
    }
    else
    {
        int n = atol(argv[1]);
        printf("%d! = %d\n", n, factorielle(n)); 
    }
}