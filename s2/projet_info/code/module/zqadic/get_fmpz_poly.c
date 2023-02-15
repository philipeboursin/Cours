#include "zqadic.h"

void zqadic_get_fmpz_poly(fmpz_poly_t rop, zqadic_t op, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_get_fmpz_poly(rop, op, zqadic_ctx -> pctx);
}