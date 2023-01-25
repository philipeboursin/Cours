#include "n2adic.h"

/* Free d'un n2adic_t */
void n2adic_clear(n2adic_t x)
{
    padic_poly_clear(x);
}