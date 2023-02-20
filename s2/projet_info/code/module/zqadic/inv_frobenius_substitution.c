#include "zqadic.h"

void zqadic_choisi_coeff(zqadic_t rop, zqadic_t op, int j, zqadic_ctx_t ctx)
{
    slong N = zqadic_prec(rop);
    slong d = ctx -> deg;
    slong p = fmpz_get_si(ctx -> p);

    padic_t cache;

    padic_init2(cache, N);

    for (slong k = 0; p*k + j < d; k++)
    {
        padic_poly_get_coeff_padic(cache, op, p*k + j, ctx -> pctx);
        padic_poly_set_coeff_padic(rop, k, cache, ctx -> pctx);
    }

    padic_clear(cache);
}

void _zqadic_inv_frobenius_substitution(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    slong N = zqadic_prec(rop);

    if ((ctx -> type) == TEICHMULLER || N == 1)
    {
        slong p = fmpz_get_si(ctx -> p);

        zqadic_t cache1, cache2, sum;

        zqadic_init2(cache1, N, ctx);
        zqadic_init2(cache2, N, ctx);
        zqadic_init2(sum, N, ctx);

        zqadic_zero(sum);
        for (slong j = 0; j < p; j++)
        {
            zqadic_set(cache1, (ctx -> C)[j], ctx);
            zqadic_zero(cache2);
            zqadic_choisi_coeff(cache2, op, j, ctx);
            zqadic_mul(cache1, cache1, cache2, ctx);
            zqadic_add(sum, sum, cache1, ctx);
        }
        zqadic_set(rop, sum, ctx);

        zqadic_clear(cache1);
        zqadic_clear(cache2);
        zqadic_clear(sum);
    }
    else
    {
        printf("zqadic_inv_frobenius_substitution exception : non implémenté.");
        exit(-1);
    }
}

void zqadic_inv_frobenius_substitution(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    slong prec = zqadic_prec(rop);
 
    zqadic_t rop_auxi, op_auxi;

    zqadic_init2(rop_auxi, prec, ctx);
    zqadic_init2(op_auxi, prec, ctx);
    
    zqadic_set(op_auxi, op, ctx);
    _zqadic_inv_frobenius_substitution(rop_auxi, op_auxi, ctx);
    zqadic_set(rop, rop_auxi, ctx);

    zqadic_clear(rop_auxi);
    zqadic_clear(op_auxi);
}