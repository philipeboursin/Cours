#include "zqadic.h"

/* Suppose que x est réduit */
int zqadic_is_one(zqadic_t x)
{
    return padic_poly_is_one(x);
}