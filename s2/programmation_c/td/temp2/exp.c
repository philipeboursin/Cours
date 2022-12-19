#include<stdio.h>
#include "gmp.h"


//------
// Exponentiation modulaire sur des grands entiers
void fast_exp(mpz_t res, mpz_t x, mpz_t k, mpz_t n);
// Test de la fonction d'exponentiation rapide
void test1();
// Chiffremenet d'un message avec RSA
void test2();


//------
void fast_exp(mpz_t res, mpz_t x, mpz_t k, mpz_t n)
{
    mpz_t temp_res;
    mpz_t temp_k;
    mpz_t pow;
    mpz_t r;
    mpz_t const_0;
    mpz_t const_1;
    mpz_t const_2;

    mpz_init_set_d(temp_res, 1);
    mpz_init_set(temp_k, k);
    mpz_init_set(pow, x);
    mpz_mod(pow, pow, n);
    mpz_init(r);
    mpz_init_set_d(const_0, 0);
    mpz_init_set_d(const_1, 1);
    mpz_init_set_d(const_2, 2);

    while (mpz_cmp(temp_k, const_0) != 0)
    {
        mpz_fdiv_r(r, temp_k, const_2);
        if (mpz_cmp(r, const_1) == 0)
        {
            mpz_mul(temp_res, temp_res, pow);
            mpz_mod(temp_res, temp_res, n);
        }
        mpz_mul(pow, pow, pow);
        mpz_mod(pow, pow, n);
        mpz_fdiv_q(temp_k, temp_k, const_2);
    }

    mpz_set(res, temp_res);

    mpz_clear(temp_res);
    mpz_clear(temp_k);
    mpz_clear(pow);
    mpz_clear(r);
    mpz_clear(const_0);
    mpz_clear(const_1);
    mpz_clear(const_2);
}

void test1()
{
    mpz_t res;
    mpz_t x;
    mpz_t k;
    mpz_t n;
    
    mpz_init(res);
    mpz_init_set_str(x, "2", 10);
    mpz_init_set_str(k, "10", 10);
    mpz_init_set_str(n, "100", 10);
    
    fast_exp(res, x, k, n);
    gmp_printf("%Zd\n", res);
}

void test2()
{
    mpz_t m;
    mpz_t p;
    mpz_t q;
    mpz_t e;
    mpz_t n;
    mpz_t chiffre;

    mpz_init_set_str(m, "38817594430224640531948138935390316817521938816897081155369678977430491610293", 10);
    mpz_init_set_str(p, "66288176273580998209477836248669781909129396031562813740315924314972782813923", 10);
    mpz_init_set_str(q, "48605347250683966724594363679449768190927730140725487943059368852545853253907", 10);
    mpz_init_set_str(e, "8550423785110472851", 10);
    mpz_init(n);
    mpz_mul(n, p, q);
    mpz_init(chiffre);

    fast_exp(chiffre, m, e, n);
    gmp_printf("%Zd\n", chiffre);
}


//-----
int main()
{
    // test1(); 
    test2();
}