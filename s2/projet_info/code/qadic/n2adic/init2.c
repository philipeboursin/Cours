#include "n2adic.h"

// Initialise x à la précision donnée en argument prec
void n2adic_init2(n2adic_t x, int prec, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_init2(x, n2adic_ctx -> deg, prec);
}