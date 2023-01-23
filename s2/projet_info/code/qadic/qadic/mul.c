#include "qadic.h"

void qadic_mul(qadic_t rop, qadic_t op1, qadic_t op2, qadic_ctx_t qadic_ctx)
{
    padic_poly_mul(rop, op1, op2, (*qadic_ctx).C);
    qadic_reduce(rop, qadic_ctx);
}