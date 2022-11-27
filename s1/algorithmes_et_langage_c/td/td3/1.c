#include<stdio.h>


// Exponentiation rapide en partant des bits de poids faible
int fast_exp_modn(int x, unsigned int k, unsigned int n);
// Tests de la question 1
void q1();
// Exponentiation rapide en partant des bits de poids fort
int fast_exp_modn_bis(int x, unsigned int k, unsigned int n);
// Tests de la question 2
void q2();


//------ Question 1
int fast_exp_modn(int x, unsigned int k, unsigned int n)
{
    int res = 1;
    int pow = x % n;
    while (k != 0)
    {
        if (k & 1 == 1)
        {
            res = (res * pow) % n;
        
        }
        pow = (pow * pow) % n;
        k = k >> 1;
    }
    return res;
}

void q1()
{
    int x = 2;
    unsigned int k = 5;
    unsigned int n = 7;
    printf("%d\n", fast_exp_modn(x, k, n));
}


//------- Question 2
int fast_exp_modn_bis(int x, unsigned int k, unsigned int n)
{
    int res = 1;
    int i = __builtin_clz(k|1) + (!k);
    while (i != 0)
    {
        res = (res * res) % n;
        if (((k >> (i - 1)) & 0x1) == 1)
        {
            res = (res * x) % n;
        }
        i--;
    }
    return res;
}


void q2()
{
    int x = 10;
    unsigned int k = 14;
    unsigned int n = 13;
    printf("%d\n", fast_exp_modn(x, k, n));
    printf("%d\n", fast_exp_modn_bis(x, k, n));
}


//-------
int main()
{
    q1();
    q2();
}