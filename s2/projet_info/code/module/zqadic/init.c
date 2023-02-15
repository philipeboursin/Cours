#include "zqadic.h"

// Initialise x à la précision de l'extension
void zqadic_init(zqadic_t x, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_init2(x, zqadic_ctx -> deg, zqadic_ctx -> prec);
}