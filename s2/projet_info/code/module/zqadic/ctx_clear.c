#include "zqadic.h"

void zqadic_ctx_clear(zqadic_ctx_t ctx)
{
    slong p = fmpz_get_si(ctx -> p);
    for (slong j = 0; j < p; j++) zqadic_clear((ctx -> C)[j]);
    free(ctx -> C);
    padic_poly_clear(ctx -> M);
    padic_ctx_clear(ctx -> pctx);
    fmpz_clear(ctx -> p);
}