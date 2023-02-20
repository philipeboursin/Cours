#include "zqadic.h"

void zqadic_add(zqadic_t rop, zqadic_t op1, zqadic_t op2, zqadic_ctx_t ctx)
{
    padic_poly_add(rop, op1, op2, ctx -> pctx); // La réduction ici est inutile puisque l'addition de deux polynômes ne fait pas monter le degré (on suppose que op1 et op2 sont réduits)
}