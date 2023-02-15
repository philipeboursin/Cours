#include "zqadic.h"

/* Free d'un zqadic_t */
void zqadic_clear(zqadic_t x)
{
    padic_poly_clear(x);
}