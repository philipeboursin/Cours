#include "zqadic.h"

void zqadic_neg(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    padic_poly_neg(rop, op, ctx -> pctx);
}