#include "n2adic.h"

slong n2adic_val(n2adic_t x)
{
    return padic_poly_val(x);
}