#include "../qadic.h"

void qadic_init(qadic_t x, qadic_ctx_t qadic_ctx)
{
    padic_poly_init2(x, (*qadic_ctx).n, (*qadic_ctx).N);
}