#include "zqadic.h"


// COMPLETER CE TEST
int main()
{
    int prec = 10;
    int deg = 5;
    flint_rand_t state;
    zqadic_ctx_t ctx_teich;
    // zqadic_ctx_t ctx_sparse;
    zqadic_t x;
    zqadic_t y;

    flint_randinit(state);
    zqadic_ctx_init_teichmuller(ctx_teich, deg, prec, 0, prec, PADIC_TERSE);
    zqadic_init2(x, prec, ctx_teich);
    zqadic_init2(y, prec - 1, ctx_teich);

    zqadic_randtest(x, state, ctx_teich);
    zqadic_print(x, ctx_teich);
    printf("\n");

    zqadic_set(y, x, ctx_teich);
    zqadic_frobenius_substitution(y, y, ctx_teich);

    zqadic_print(y, ctx_teich);    
    printf("\n");

    zqadic_clear(x);
    zqadic_clear(y);
    zqadic_ctx_clear(ctx_teich);
    flint_randclear(state);
}