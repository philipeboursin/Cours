#include "n2adic.h"

void n2adic_print(n2adic_t x, n2adic_ctx_t ctx)
{
    padic_poly_print(x, ctx -> pctx);
}