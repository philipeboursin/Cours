#include "zqadic.h"

void zqadic_randtest(zqadic_t x, flint_rand_t state, zqadic_ctx_t ctx)
{
    int val = -1;
    while (val < 0)
    {
        padic_poly_randtest(x, state, ctx -> deg, ctx -> pctx);
        val = padic_poly_val(x);
    }
}