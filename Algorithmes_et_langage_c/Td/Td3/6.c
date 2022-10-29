#include<stdio.h>


// Calcule le symbôle de Legendre de a sur b, b étant un entier premier impair
int legendre(int a, int b);
// Tests de la question 1
void q1();
// Tests de la question 2
void q2();


//------
int legendre(int a, int b)
{
    if (a % b == 0)
    {
        return 0;
    }
    else
    {
        int c;
        int res = 1;
        while ((a != 1) && (b != 1))
        {
            a = a % b;
            while ((a & 1) == 0)
            {
                res *= ((b & 0b111) == 7 || (b & 0b111) == 1) - ((b & 0b111) == 5 || (b & 0b111) == 3);
                a = a >> 1;
            }
            res *= 1 - 2*(((a & 0b11) == 3) && ((b & 0b11) == 3));
            c = a;
            a = b;
            b = c;
        }
        return res;
    }
}

void q1()
{
    int a = 5;
    int b = 3;
    int f1 = ((a & 0b111) == 7 || (a & 0b111) == 1) - ((a & 0b111) == 5 || (a & 0b111) == 3);
    int f2 = -1 + 2*(((a & 0b11) == 3) && ((b & 0b11) == 3));
    printf("%d %d\n", f1, f2);
}

void q2()
{
    int P[5] = {3, 5, 7, 11, 13};
    int p;
    for (int i = 0; i < 5; i++)
    {
        p = P[i];
        for (int j = 0; j < p; j++)
        {
            printf("%d ", legendre(j, p));
        }
        printf("\n");
    }
}


//------
int main()
{
    q1();
    q2();
}