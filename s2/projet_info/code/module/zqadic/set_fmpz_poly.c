#include "zqadic.h"

void zqadic_set_fmpz_poly(zqadic_t rop, fmpz_poly_t op, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_set_fmpz_poly(rop, op, zqadic_ctx -> pctx);
}