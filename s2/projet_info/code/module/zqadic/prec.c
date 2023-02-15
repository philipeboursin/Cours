#include "zqadic.h"

// Retourne la précision de x \in Q_q
slong zqadic_prec(zqadic_t x)
{
    return padic_poly_prec(x);
}