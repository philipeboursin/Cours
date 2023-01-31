#include "n2adic.h"

/* Free d'un contexte $2^n$-adique */
void n2adic_ctx_clear(n2adic_ctx_t ctx)
{
    slong p = fmpz_get_si(ctx -> p);
    for (slong j = 0; j < p; j++)
    {
        n2adic_clear((ctx -> C)[j]);
    } 
    free(ctx -> C);
    padic_poly_clear(ctx -> M);
    padic_ctx_clear(ctx -> ctx);
    fmpz_clear(ctx -> p);
}