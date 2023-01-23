#include "qadic.h"

void qadic_print(qadic_t x, qadic_ctx_t qadic_ctx)
{
    padic_poly_print(x, (*qadic_ctx).C);
}