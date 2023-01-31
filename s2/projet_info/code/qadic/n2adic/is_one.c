#include "n2adic.h"

/* Suppose que x est réduit */
int n2adic_is_one(n2adic_t x)
{
    return padic_poly_is_one(x);
}