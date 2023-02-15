#include "zqadic.h"

void zqadic_ctx_rep(padic_poly_t P, zqadic_ctx_t ctx)
{
    padic_poly_set(P, ctx -> M, ctx -> pctx);
}