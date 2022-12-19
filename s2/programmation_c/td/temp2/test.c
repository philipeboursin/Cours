#include "gmp.h"

int main()
{
    mpz_t n;
    mpz_init(n);
    mpz_set_d(n, 10);
    gmp_printf("%Zd\n", n);
}