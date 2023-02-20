#include "zqadic.h"

int zqadic_equal(zqadic_t x, zqadic_t y)
{
    return padic_poly_equal(x, y);
}