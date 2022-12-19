#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>


//-----
// Factorisation naïve
void factor(mpz_t n, mpz_t facteurs[2]);
// Factorisation avec astuce de Fermat
void factor_fermat(mpz_t n, mpz_t facteurs[2]);
// Test de la factorisation naïve
void test1();


//-----
void factor(mpz_t n, mpz_t facteurs[2])
{
    mpz_t i;
    mpz_t inter;
    int b = 1;
    
    mpz_init_set_ui(i, 2);
    mpz_init(inter);

    while (b)
    {
        if (mpz_divisible_p(n, i) != 0)
        {
            mpz_set(facteurs[0], i);
            mpz_fdiv_q(inter, n, i);
            mpz_set(facteurs[1], inter);
            b = 0;
        }
        mpz_add_ui(i, i, 1);
    }
}

void factor_fermat(mpz_t n, mpz_t facteurs[2])
{
    mpz_t N;
    mpz_t d;
    mpz_t inter;

    mpz_init_set_ui(d, 0);
    mpz_init_set(N, n);
    mpz_init(inter);

    while (mpz_root(inter, N, 2) == 0)
    {
        mpz_add_ui(d, d, 1);
        mpz_mul(inter, d, d);
        mpz_add(N, n, inter);
    }

    mpz_sub(facteurs[0], inter, d);
    mpz_add(facteurs[1], inter, d);
}

void test1()
{
    long unsigned int* primes;
    mpz_t facteurs[2];
    mpz_t n;
    mpz_t inter;

    mpz_init(facteurs[0]);
    mpz_init(facteurs[1]);
    mpz_init(inter);
    mpz_init_set_str(n, "41425321056593929672502264616970281911913149005819425885159431425752790059367703311", 10);

    factor(n, facteurs);
    gmp_printf("%Zd %Zd\n", facteurs[0], facteurs[1]);
    mpz_mul(inter, facteurs[0], facteurs[1]);
    gmp_printf("Vérification de la factorisation : %d\n", mpz_cmp(n, inter) == 0);

    //Pour ce nombre, la méthode naïve ne fonctionne pas. On utilise la méthode avec astuce de fermat.
    mpz_init_set_str(n, "27213716393115405899585017099144506859069883524026398140546466358968552604221965528003533461593034488719126775594181767016502660263535778871320377888521", 10);
    factor_fermat(n, facteurs);
    gmp_printf("%Zd %Zd\n", facteurs[0], facteurs[1]);
    mpz_mul(inter, facteurs[0], facteurs[1]);
    gmp_printf("Vérification de la factorisation : %d\n", mpz_cmp(n, inter) == 0);
}


//-----
int main()
{
    test1();
}