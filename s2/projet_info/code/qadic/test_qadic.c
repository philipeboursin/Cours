#include "stdio.h"
#include "stdlib.h"
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>
#include "qadic.h"


void test(padic_ctx_t C)
{
    padic_poly_t m;
    padic_poly_t M;
    padic_t un;
    int N = 10;
    
    padic_poly_init2(m, 9, 1);
    padic_poly_init2(M, 0, N);
    padic_init2(un, 1);
    padic_one(un);

    padic_poly_set_coeff_padic(m, 0, un, C);
    padic_poly_set_coeff_padic(m, 2, un, C);
    padic_poly_set_coeff_padic(m, 3, un, C);
    padic_poly_set_coeff_padic(m, 4, un, C);
    padic_poly_set_coeff_padic(m, 8, un, C);

    _teichmuller_modulus(M, m, N, C);

    padic_poly_print(M, C);
    printf("\n");

    padic_poly_clear(m);
    padic_poly_clear(M);
    padic_clear(un);
}

void main()
{
    // Initialisation du contexte
    fmpz_t p;
    padic_ctx_t C;
    fmpz_init_set_si(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_TERSE);

    // Tests
    // test1(C);
    // test2(C);
    // test3(C);
    test(C);

    fmpz_clear(p);
    padic_ctx_clear(C);
}