#include "n2adic.h"


// COMPLETER CE TEST
int main()
{
    int prec = 10;
    int deg = 5;
    flint_rand_t state;
    n2adic_ctx_t ctx;
    n2adic_t x;
    n2adic_t y;

    flint_randinit(state);
    n2adic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    n2adic_init2(x, prec, ctx);
    n2adic_init2(y, prec - 1, ctx);

    n2adic_randtest(x, state, ctx);
    n2adic_print(x, ctx);
    printf("\n");

    n2adic_set(y, x, ctx);
    n2adic_frobenius_substitution(y, y, ctx);

    n2adic_print(y, ctx);    
    printf("\n");

    n2adic_clear(x);
    n2adic_clear(y);
    n2adic_ctx_clear(ctx);
    flint_randclear(state);
}