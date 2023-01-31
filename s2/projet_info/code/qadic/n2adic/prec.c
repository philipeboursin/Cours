#include "n2adic.h"

// Retourne la précision de x \in Q_q
slong n2adic_prec(n2adic_t x)
{
    return padic_poly_prec(x);
}