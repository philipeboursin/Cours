#include "zqadic.h"

void zqadic_set_padic(zqadic_t rop, padic_t op, zqadic_ctx_t ctx)
{
    padic_poly_set_padic(rop, op, ctx -> pctx);
}