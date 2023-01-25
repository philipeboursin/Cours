#include "n2adic.h"

/* Free d'un contexte $2^n$-adique */
void n2adic_ctx_clear(n2adic_ctx_t n2adic_ctx)
{
    padic_poly_clear((*n2adic_ctx).M);
    padic_ctx_clear((*n2adic_ctx).ctx);
}