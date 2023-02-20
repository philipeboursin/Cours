#include "zqadic.h"

int zqadic_is_one(zqadic_t x)
{
    return padic_poly_is_one(x);
}