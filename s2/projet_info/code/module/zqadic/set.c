#include "zqadic.h"

void zqadic_set(zqadic_t rop, zqadic_t op, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_set(rop, op, zqadic_ctx -> pctx);
}