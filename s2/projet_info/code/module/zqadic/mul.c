#include "zqadic.h"

void zqadic_mul(zqadic_t rop, zqadic_t op1, zqadic_t op2, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_mul(rop, op1, op2, zqadic_ctx -> pctx);
    zqadic_reduce(rop, zqadic_ctx);
}