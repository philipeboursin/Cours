#include "n2adic.h"

void n2adic_ctx_rep(padic_poly_t P, n2adic_ctx_t ctx)
{
    padic_poly_set(P, ctx -> M, ctx -> pctx);
}