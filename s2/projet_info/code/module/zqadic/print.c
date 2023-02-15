#include "zqadic.h"

void zqadic_print(zqadic_t x, zqadic_ctx_t ctx)
{
    padic_poly_print(x, ctx -> pctx);
}