#include<stdio.h>


// Algorithme d'euclide étendu
void euclide(int a, int b, int* rr, int* u, int* v);
// Tests de la question 1
void q1();
// Calcul d'une inverse modulo n
int inverse_modn(int a, int n);
// Tests de la question 2
void q2();


//------ Question 1
void euclide(int a, int b, int* rr, int* u, int* v)
{
    int u1 = 1;
    int v1 = 0;
    int u2 = 0;
    int v2 = 1;
    int r;
    int q;
    int bu; //buffer u2
    int bv; //buffer u1
    while (b)
    {
        r = a % b;
        q = a / b;
        bu = u2;
        bv = v2;
        u2 = u1 - q*u2;
        v2 = v1 - q*v2;
        a = b;
        b = r;
        u1 = bu;
        v1 = bv;
    }
    *rr = a;
    *u= u1;
    *v = v1;
}

void q1()
{
    int a = 10;
    int b = 17;
    int r;
    int u;
    int v;
    euclide(a, b, &r, &u, &v);
    printf("%d, %d, %d, %d\n", u, v, r, a*u + b*v == r);
}


//------ Question 2
int inverse_modn(int a, int n)
{
    int r;
    int u;
    int v;
    euclide(a % n, n, &r, &u, &v);
    printf("%d,%d,%d\n", a, n, u);
    if (r != 1)
    {
        printf("%d n'est pas inversible modulo %d\n", a, n);
        return -1;
    }
    else return u % n;
}

void q2()
{
    printf("%d\n", -3%10);
    int n = 10;
    int a = 3;
    int res = inverse_modn(a, n);

    if (res != -1)
    {
        printf("%d, %d, %d\n", a, res, (a*res) % n);
    }
}


//------
int main()
{
    q1();
    q2();
}