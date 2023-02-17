#include "zqadic.h"

int main()
{
    int prec = 10;
    int deg = 5;
    fmpz_t deux;
    flint_rand_t state;
    padic_ctx_t pctx;
    zqadic_ctx_t ctx_teich;
    zqadic_ctx_t ctx_sparse;
    zqadic_t x;
    zqadic_t y;
    padic_poly_t M;
    fmpz_poly_t m;

    flint_randinit(state);

    padic_poly_init2(M, deg + 1, prec);
    fmpz_poly_init(m);

    fmpz_init_set_ui(deux, 2);
    padic_ctx_init(pctx, deux, 0, prec, PADIC_TERSE);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 1, 562);
    fmpz_poly_set_coeff_si(m, 2, 1019);
    fmpz_poly_set_coeff_si(m, 3, 21);
    fmpz_poly_set_coeff_si(m, 4, 523);
    fmpz_poly_set_coeff_si(m, 5, 134);
    fmpz_poly_set_coeff_si(m, 6, 842);
    fmpz_poly_set_coeff_si(m, 7, 644);
    fmpz_poly_set_coeff_si(m, 8, 1);
    padic_poly_set_fmpz_poly(M, m, pctx);

    printf("M = ");
    padic_poly_print(M, pctx);
    printf("\n");

    zqadic_ctx_init_padic_poly(ctx_teich, M, pctx, TEICHMULLER);
    zqadic_ctx_init_padic_poly(ctx_sparse, M, pctx, SPARSE);

    zqadic_init(x, ctx_teich);
    zqadic_init(y, ctx_teich);

    for (int i = 0; i < 10; i++) zqadic_randtest(x, state, ctx_sparse);

    zqadic_frobenius_substitution(y, x, ctx_sparse);
    printf("M = ");
    zqadic_print(y, ctx_teich);
    printf("\n");

    zqadic_frobenius_substitution(y, x, ctx_teich);
    printf("M = ");
    zqadic_print(y, ctx_sparse);
    printf("\n");
}