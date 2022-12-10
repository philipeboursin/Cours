#include "gmp.h"

void fast_exp(mpz_t x, mpz_t k, mpz_t res)
{
    mpz_t pow;
    mpz_t r;
    mpz_t const_0;
    mpz_t const_1;
    mpz_t const_2;

    mpz_set_d(res, 1);
    mpz_init_set(pow, x);
    mpz_init(r);
    mpz_init_set_d(const_0, 0);
    mpz_init_set_d(const_1, 1);
    mpz_init_set_d(const_2, 2);
    mpz_cdiv_r(r, const_1, const_2);
    gmp_printf("%Zd\n", r);



    while (mpz_cmp(k, const_0) != 0)
    {
        mpz_cdiv_r(r, k, const_2);
        if (mpz_cmp(r, const_1) == 0)
        {
            mpz_mul(res, res, pow);
        }
        mpz_mul(pow, pow, pow);
        mpz_cdiv_q(k, k, const_2);
        // gmp_printf("%Zd\n", k);
    }

    mpz_clear(pow);
    mpz_clear(r);
    mpz_clear(const_0);
    mpz_clear(const_1);
    mpz_clear(const_2);
}

int main()
{
    mpz_t x;
    mpz_t k;
    mpz_t res;
    mpz_init_set_d(x, 2);
    mpz_init_set_d(k, 10);
    mpz_init(res);
    fast_exp(x, k, res);
    gmp_printf("%Zd\n", res);
}