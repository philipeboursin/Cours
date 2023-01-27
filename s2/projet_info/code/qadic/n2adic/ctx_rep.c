#include "n2adic.h"

void n2adic_ctx_rep(padic_poly_t P, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_set(P, n2adic_ctx -> M, n2adic_ctx -> ctx);
}