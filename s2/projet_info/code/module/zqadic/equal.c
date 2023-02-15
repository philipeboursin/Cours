#include "zqadic.h"

/* Suppose que x et y sont dans leur forme réduite */
int zqadic_equal(zqadic_t x, zqadic_t y)
{
    return padic_poly_equal(x, y);
}