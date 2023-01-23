#include "n2adic.h"

void n2adic_init(n2adic_t x, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_init2(x, (*n2adic_ctx).n, (*n2adic_ctx).N);
}