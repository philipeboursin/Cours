#include "n2adic.h"

// void _n2adic_Cj(n2adic_t C_0, n2adic_t C_1, n2adic_ctx_t ctx)
// {
//     slong N = n2adic_prec(C_0);
//     slong d = ctx -> deg;
//     // j = 0
//     n2adic_one(C_0);

//     // j = 1
//     padic_t un;
//     padic_init2(un, N);
//     padic_one(un);
//     padic_poly_set_coeff_padic(C_1, n_pow(2, d - 1), un, ctx -> ctx); // A modifier, coder une exponentiation rapide modulaire sur les entiers 2^d adiques
//     n2adic_reduce(C_1, ctx);
//     padic_clear(un);
// }

void _n2adic_choisi_coeff(n2adic_t rop, n2adic_t op, int j, n2adic_ctx_t ctx)
{
    slong N = n2adic_prec(rop);
    slong d = ctx -> deg;

    padic_t cache;
    padic_init2(cache, N);

    for (slong k = 0; 2*k + j < d; k++)
    {
        padic_poly_get_coeff_padic(cache, op, 2*k + j, ctx -> ctx);
        padic_poly_set_coeff_padic(rop, k, cache, ctx -> ctx);
    }

    padic_clear(cache);
}

void n2adic_inv_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx)
{
    slong N = n2adic_prec(rop);
    slong p = fmpz_get_si(ctx -> p);

    n2adic_t op_auxi; // Pour emmener op à la précision de rop.
    n2adic_init2(op_auxi, N, ctx);
    n2adic_set(op_auxi, op, ctx);

    n2adic_t cache1;
    n2adic_t cache2;
    n2adic_t sum;
    n2adic_init2(cache1, N, ctx);
    n2adic_init2(cache2, N, ctx);
    n2adic_init2(sum, N, ctx);

    n2adic_zero(sum);

    for (slong j = 0; j < p; j++)
    {
        n2adic_set(cache1, (ctx -> C)[j], ctx);
        _n2adic_choisi_coeff(cache2, op_auxi, j, ctx);
        n2adic_mul(cache1, cache1, cache2, ctx);
        n2adic_add(sum, sum, cache1, ctx);
    }

    n2adic_set(rop, sum, ctx);

    // n2adic_t C_0;
    // n2adic_t C_1;
    // n2adic_init2(C_0, N, ctx);
    // n2adic_init2(C_1, N, ctx);
    // n2adic_set(C_0, (ctx -> C)[0], ctx);
    // n2adic_set(C_1, (ctx -> C)[1], ctx);

    // n2adic_t cache0;
    // n2adic_t cache1;
    // n2adic_init2(cache0, N, ctx);
    // n2adic_init2(cache1, N, ctx);

    // _n2adic_choisi_coeff(cache0, op_auxi, 0, ctx);
    // n2adic_mul(cache0, C_0, cache0, ctx);
    // _n2adic_choisi_coeff(cache1, op_auxi, 1, ctx);
    // n2adic_mul(cache1, C_1, cache1, ctx);
    // n2adic_add(rop, cache0, cache1, ctx);

    n2adic_clear(op_auxi);
    n2adic_clear(cache1);
    n2adic_clear(cache2);
    n2adic_clear(sum);
}