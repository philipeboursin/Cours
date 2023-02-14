#include "n2adic.h"

void n2adic_set(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_set(rop, op, n2adic_ctx -> pctx);
}