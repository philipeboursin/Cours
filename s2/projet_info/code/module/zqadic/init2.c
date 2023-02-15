#include "zqadic.h"

// Initialise x à la précision donnée en argument prec
void zqadic_init2(zqadic_t x, slong prec, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_init2(x, zqadic_ctx -> deg, prec);
}