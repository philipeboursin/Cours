#include "zqadic.h"

void zqadic_sub(zqadic_t rop, zqadic_t op1, zqadic_t op2, zqadic_ctx_t ctx)
{
    padic_poly_sub(rop, op1, op2, ctx -> pctx);
}