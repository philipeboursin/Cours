#include "n2adic.h"

int main()
{
    int deg = 6;
    int prec = 10;

    flint_rand_t state;
    flint_randinit(state);

    n2adic_ctx_t ctx;
    n2adic_t x;
    n2adic_t y;
    
    n2adic_ctx_init(ctx, deg, prec, 0, prec, PADIC_TERSE);
    n2adic_init(x, ctx);
    n2adic_init(y, ctx);

    int b = 1;
    for(int i = 0; i < 1000; i++)
    {
        n2adic_randtest(x, state, ctx);
        n2adic_inv_frobenius_substitution(y, x, ctx);
        n2adic_frobenius_substitution(y, y, ctx);
        if(n2adic_equal(x, y) != 1)
        {
            b = 0;
        }
    }
    printf("%d\n", b);

    flint_randclear(state);
    n2adic_clear(x);
    n2adic_clear(y);
    n2adic_ctx_clear(ctx);
}