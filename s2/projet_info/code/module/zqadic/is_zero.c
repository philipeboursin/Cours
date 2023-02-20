#include "zqadic.h"

int zqadic_is_zero(zqadic_t x)
{
    return padic_poly_is_zero(x);
}