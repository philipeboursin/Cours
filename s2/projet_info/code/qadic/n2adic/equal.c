#include "n2adic.h"

/* Suppose que x et y sont dans leur forme réduite */
int n2adic_equal(n2adic_t x, n2adic_t y)
{
    return padic_poly_equal(x, y);
}