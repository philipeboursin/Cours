#include "n2adic.h"

void n2adic_print(n2adic_t x, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_print(x, n2adic_ctx -> ctx);
}