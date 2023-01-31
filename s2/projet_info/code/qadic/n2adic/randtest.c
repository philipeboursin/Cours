#include "n2adic.h"

void n2adic_randtest(n2adic_t x, flint_rand_t state, n2adic_ctx_t ctx)
{
    padic_poly_randtest_val(x, state, 0, ctx -> deg, ctx -> ctx);
}