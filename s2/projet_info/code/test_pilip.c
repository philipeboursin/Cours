#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>

int test1()
{
    flint_rand_t state;
    fmpz_t p;
    padic_ctx_t C;
    padic_t x;
    padic_t y;

    flint_randinit(state);
    fmpz_init_set_ui(p, 7);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_init2(x, 2);
    padic_init2(y, 1);

    padic_set_ui(y, 5, C);
    padic_add(x, y, y, C);
    padic_print(x, C);
    printf("\n");

    flint_randclear(state);
    fmpz_clear(p);
    padic_ctx_clear(C);
    padic_clear(x);
    padic_clear(y);
}

int test2()
{
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_t C;
    padic_poly_t m;
    padic_poly_t n;
    padic_poly_t rop;
    padic_t un;
    int N = 10;

    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_poly_init2(m, 9, 1);
    padic_poly_init2(n, 9, 1);
    padic_poly_init2(rop, 0, 2);

    padic_init(un);
    padic_one(un);

    padic_poly_set_coeff_padic(m, 0, un, C);
    padic_poly_set_coeff_padic(m, 2, un, C);
    padic_poly_set_coeff_padic(m, 3, un, C);
    padic_poly_set_coeff_padic(m, 4, un, C);
    padic_poly_set_coeff_padic(m, 8, un, C);

    padic_poly_set_coeff_padic(n, 0, un, C);
    padic_poly_set_coeff_padic(n, 2, un, C);
    padic_poly_set_coeff_padic(n, 4, un, C);
    padic_poly_set_coeff_padic(n, 8, un, C);
    // padic_neg(un, un, C);

    // padic_print(un, C);
    // printf("\n");

    padic_poly_set_coeff_padic(n, 3, un, C);

    padic_poly_print(m, C);
    printf("\n");
    padic_poly_print(n, C);
    printf("\n");

    padic_poly_add(rop, m, n, C);

    padic_poly_print(rop, C);
    printf("\n");

    padic_poly_clear(rop);
    padic_poly_clear(m);
    padic_clear(un);
    padic_ctx_clear(C);
}

void test3()
{
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_t C;
    padic_poly_t m;
    padic_poly_t n;
    padic_poly_t rop;
    padic_t un;
    int N = 10;

    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_poly_init2(m, 9, 2);
    padic_poly_init2(n, 9, 3);

    padic_init(un);
    padic_one(un);

    padic_poly_set_coeff_padic(m, 0, un, C);
    padic_poly_set_coeff_padic(m, 2, un, C);
    padic_poly_set_coeff_padic(m, 4, un, C);
    padic_poly_set_coeff_padic(m, 8, un, C);
    padic_neg(un, un, C);

    padic_print(un, C);
    printf("\n");
    padic_poly_set_coeff_padic(m, 3, un, C);

    padic_poly_print(m, C);
    printf("\n");

    padic_poly_set(n, m, C);

    padic_poly_print(n, C);
    printf("\n");

    padic_poly_clear(m);
    padic_clear(un);
    padic_ctx_clear(C);
}

void test4()
{
    fmpz_t p;
    padic_ctx_t C;
    padic_t x;

    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_init(x);
    padic_set_ui(x, 2, C);
    padic_pow_si(x, x, -1, C);

    padic_print(x, C);
    printf("\n");

    fmpz_clear(p);
    padic_ctx_clear(C);
    padic_clear(x);
}

int main()
{
    // test1();
    // test2();
    // test3();
    test4();
}