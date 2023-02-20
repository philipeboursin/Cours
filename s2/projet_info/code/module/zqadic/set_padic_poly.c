#include "zqadic.h"

void zqadic_set_padic_poly(zqadic_t rop, padic_poly_t op, zqadic_ctx_t ctx)
{
    padic_poly_set(rop, op, ctx -> pctx);
}