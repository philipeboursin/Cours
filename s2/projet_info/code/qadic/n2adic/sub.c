#include "n2adic.h"

void n2adic_sub(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx)
{
    padic_poly_sub(rop, op1, op2, ctx->ctx);
}