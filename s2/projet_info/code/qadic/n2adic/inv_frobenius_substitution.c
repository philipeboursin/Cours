#include "n2adic.h"

void _n2adic_choisi_coeff(n2adic_t rop, n2adic_t op, int j, n2adic_ctx_t ctx)
{
    slong N = n2adic_prec(rop);
    slong d = ctx -> deg;

    padic_t cache;
    padic_init2(cache, N);

    for (slong k = 0; 2*k + j < d; k++)
    {
        padic_poly_get_coeff_padic(cache, op, 2*k + j, ctx -> pctx);
        padic_poly_set_coeff_padic(rop, k, cache, ctx -> pctx);
    }

    padic_clear(cache);
}

void n2adic_inv_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx)
{
    if ((ctx -> type) == TEICHMULLER)
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

        n2adic_clear(op_auxi);
        n2adic_clear(cache1);
        n2adic_clear(cache2);
        n2adic_clear(sum);
    }
        else if ((ctx -> type) == SPARSE)
    {
        printf("Erreur : non implémenté.");
    }
    else
    {
        printf("Erreur : non implémenté.");
    }
}