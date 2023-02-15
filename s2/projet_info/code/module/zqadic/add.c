#include "zqadic.h"

/* Additionne deux éléments de \mathbb{Q}_{2^d}. Pour cela, additionne les polynômes à coefficients dans \mathbb{Q}_2 les représentant et réduit le résultat modulo le polynôme définissant l'extension. Supporte l'aliasing */
void zqadic_add(zqadic_t rop, zqadic_t op1, zqadic_t op2, zqadic_ctx_t zqadic_ctx)
{
    padic_poly_add(rop, op1, op2, zqadic_ctx -> pctx); // La réduction ici est inutile puisque l'addition de deux polynômes ne fait pas monter le degré (on suppose que op1 et op2 sont réduits)
}