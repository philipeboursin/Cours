#include<stdio.h>
#include<stdlib.h>


// Affichage d'un tableau de taille n
void print_tab(unsigned int* t, int n);
// Exponentiation rapide modulo n
int fast_exp_ws_modn(unsigned int x, unsigned int k, unsigned int n);
// Crible d'Eratostene
void erathostene(unsigned int** primes, unsigned int n, int* pi_n);
// Factorisation d'un entier
void factor(unsigned int n, unsigned int* primes, unsigned int facteurs[10]);
// Tests de la question 1
void q1();
// Element primitif de Zp
unsigned int prim_Zp(unsigned int p, unsigned int* primes);
// Tests de la question 2
void q2();


//------ Fonctions génériques
void print_tab(unsigned int* t, int n)
{
    printf("[");
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d, ", t[i]);
    }
    printf("%d]", t[n-1]);
}

int fast_exp_ws_modn(unsigned int x, unsigned int k, unsigned int n)
{
    unsigned int res = 1;
    unsigned int pow = x % n;
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


//------ Q1
void erathostene(unsigned int** primes, unsigned int n, int* pi_n)
{
    unsigned int t[n];
    unsigned int inter = 2;
    unsigned int tot = 0;
    unsigned int i, j;

    // Set t a zéro
    t[0] = 1;
    t[1] = 1;
    for (i = 2; i < n; i++)
    {
        t[i] = 0;
    }

    // Met 1 dans t[j] lorsque j n'est pas premier
    while (inter*inter < n)
    {
        j = inter*inter;
        while (j < n)
        {
            t[j] = 1;
            j += inter;
        }
        j = inter + 1;
        while (t[j] == 1)
        {
            j++;
        }
        inter = j;
        tot++;
    }

    // finit de compter le nombre de nombres premiers pi_n
    for (i = inter; i < n; i++)
    {
        if (t[i] == 0) tot++;
    }
    *pi_n = tot;

    // Remplis un tableau des premiers < n
    *primes = (unsigned int*) malloc(tot*sizeof(unsigned int));
    j = 0;
    for (i = 0; i < n; i++)
    {
        if (t[i] == 0)
        {
            (*primes)[j] = i;
            j++;
        } 
    }

}

void factor(unsigned int n, unsigned int* primes, unsigned int facteurs[10])
{
    int i = 0;
    int j;
    int p = primes[0];
    for (j = 0; j < 10; j++)
    {
        facteurs[j] = 0;
    }
    j = 0;
    if (n != 0)
    {
        while (p <= n)
        {
            if ((n % p) == 0)
            {
                facteurs[j] = p;
                n = n/p;
                j++;
            }
            i++;
            p = primes[i];
        }
    }
}


void q1()
{
    unsigned int facteurs[10];
    unsigned int n = 0xffff;
    unsigned int pi_n;
    unsigned int* primes;
    erathostene(&primes, n, &pi_n);
    print_tab(primes, 10);
    printf("\n");
    factor(2345789, primes, facteurs);
    print_tab(facteurs, 10);
    printf("\n");
    free(primes);
}


//------ Q2
unsigned int prim_Zp(unsigned int p, unsigned int* primes)
{
    unsigned int facteurs[10];
    int i;
    int x = 0;
    int p_i;
    factor(p - 1, primes, facteurs);

    for (x = 1; x < p; x++)
    {
        i = 0;
        p_i = facteurs[0];
        while (p_i != 0)
        {
            if (fast_exp_ws_modn(x, (p - 1)/p_i, p) == 1) break;
            i++;
            p_i = facteurs[i];
        }
        if (p_i == 0) return x;
    }
}

void q2()
{
    unsigned int p = 7;
    unsigned int n = 0xffff;
    unsigned int pi_n;
    unsigned int* primes;
    erathostene(&primes, n, &pi_n);
    unsigned int x = prim_Zp(p, primes);
    printf("%u\n", x);
}


//------
int main()
{
    // q1();
    q2();
}