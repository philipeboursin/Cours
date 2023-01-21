#include "../qadic.h"

void qadic_set_padic_poly(qadic_t rop, padic_poly_t op, qadic_ctx_t qadic_ctx)
{
    padic_poly_set(rop, op, (*qadic_ctx).C);
}