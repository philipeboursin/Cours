#include "zqadic.h"

void zqadic_init(zqadic_t x, zqadic_ctx_t ctx)
{
    padic_poly_init2(x, ctx -> deg, ctx -> prec);
}