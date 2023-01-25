#include "n2adic.h"

void n2adic_mul(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_mul(rop, op1, op2, (*n2adic_ctx).ctx);
    n2adic_reduce(rop, n2adic_ctx);
}