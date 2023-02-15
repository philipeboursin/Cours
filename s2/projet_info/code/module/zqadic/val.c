#include "zqadic.h"

slong zqadic_val(zqadic_t x)
{
    return padic_poly_val(x);
}