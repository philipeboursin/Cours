#include "n2adic.h"

/* Additionne deux éléments de \mathbb{Q}_{2^d}. Pour cela, additionne les polynômes à coefficients dans \mathbb{Q}_2 les représentant et réduit le résultat modulo le polynôme définissant l'extension. Supporte l'aliasing */
void n2adic_add(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t n2adic_ctx)
{
    padic_poly_add(rop, op1, op2, n2adic_ctx -> ctx); // La réduction ici est inutile puisque l'addition de deux polynômes ne fait pas monter le degré (on suppose que op1 et op2 sont réduits)
}