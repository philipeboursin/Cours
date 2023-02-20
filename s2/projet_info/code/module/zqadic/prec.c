#include "zqadic.h"

slong zqadic_prec(zqadic_t x)
{
    return padic_poly_prec(x);
}