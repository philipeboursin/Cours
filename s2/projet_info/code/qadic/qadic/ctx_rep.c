#include "qadic.h"

void qadic_ctx_rep(padic_poly_t P, qadic_ctx_t C)
{
    padic_poly_set(P, (*C).M, (*C).C);
}