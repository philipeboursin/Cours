#include "n2adic.h"

void n2adic_set_fmpz_poly(n2adic_t rop, fmpz_poly_t op, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_set_fmpz_poly(rop, op, n2adic_ctx -> ctx);
}