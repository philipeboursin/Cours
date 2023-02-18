#include "zqadic.h"

void zqadic_init2(zqadic_t x, slong prec, zqadic_ctx_t zqadic_ctx)
{
    if (((zqadic_ctx -> type) == TEICHMULLER) && (prec > (zqadic_ctx -> prec)))
    {
        printf("zqadic_init2 exception : précision demandée sur x supérieure à la précision maximale du contexte.");
    }
    else padic_poly_init2(x, zqadic_ctx -> deg, prec);
}