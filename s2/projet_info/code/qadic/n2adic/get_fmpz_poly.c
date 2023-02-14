#include "n2adic.h"

void n2adic_get_fmpz_poly(fmpz_poly_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_get_fmpz_poly(rop, op, n2adic_ctx -> pctx);
}