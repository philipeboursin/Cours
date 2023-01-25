#include "n2adic.h"

void n2adic_randtest(n2adic_t x, flint_rand_t state, n2adic_ctx_t ctx)
{
    padic_poly_randtest(x, state, ctx -> deg, ctx -> ctx);
}