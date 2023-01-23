#include "qadic.h"

void qadic_add(qadic_t rop, qadic_t op1, qadic_t op2, qadic_ctx_t qadic_ctx)
{
    padic_poly_add(rop, op1, op2, (*qadic_ctx).C);
    qadic_reduce(rop, qadic_ctx);
}