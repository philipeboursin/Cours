#include "n2adic.h"

void n2adic_ctx_clear(n2adic_ctx_t ctx)
{
    fmpz_clear((*ctx).p);
    padic_poly_clear((*ctx).M);
    padic_ctx_clear((*ctx).C);
}