#include "zqadic.h"

void zqadic_set_padic_poly(zqadic_t rop, padic_poly_t op, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_set(rop, op, zqadic_ctx -> pctx);
}