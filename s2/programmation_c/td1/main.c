#include "exp.h"
#include "fact.h"
#include<stdio.h>
#include<stdlib.h>


int main(int argc, char** argv)
{
    if (argc - 1 == 1)
    {
        int n = atol(argv[1]);
        printf("%d! = %d\n", n, factorielle(n));
    }
    else if (argc - 1 == 2)
    {
        int x = atol(argv[1]);
        int k = atol(argv[2]);
        printf("%d^%d = %d\n", x, k, fast_exp(x, k));
    }
    else
    {
        printf("Mauvais nombre d'arguments !");
    }
}