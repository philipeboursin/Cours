#include "zqadic.h"

void _zqadic_newton_iteration(zqadic_t rop, padic_poly_t M, zqadic_t op, slong k, slong n, slong prec, zqadic_ctx_t ctx)
{
    if (prec <= n)
    {
        zqadic_set(rop, op, ctx);
    }
    else
    {
        slong Nr = ((prec + k) >> 1) + ((prec + k) & 1);
        padic_poly_t Mr;
        padic_poly_t Mz;
        padic_poly_t Mrz;


        padic_poly_init2(Mr, 0, padic_poly_prec(M));
        padic_poly_init2(Mz, 0, padic_poly_prec(M));
        padic_poly_init2(Mrz, 0, padic_poly_prec(M));
        padic_poly_derivative(Mr, M, ctx -> pctx);

        _zqadic_newton_iteration(rop, M, op, k, n, Nr, ctx);
        zqadic_composition(Mz, M, rop, ctx);
        zqadic_composition(Mrz, Mr, rop, ctx);
        zqadic_inv(Mrz, Mrz, ctx);
        zqadic_mul(Mrz, Mrz, Mz, ctx);
        zqadic_sub(rop, rop, Mrz, ctx);

        // FAIRE LES CLEARS
    }
}

void zqadic_newton_iteration(zqadic_t rop, padic_poly_t M, zqadic_t op, slong k, slong n, slong prec, zqadic_ctx_t ctx)
{
    zqadic_t rop_auxi;
    zqadic_init2(rop_auxi, zqadic_prec(rop), ctx);
    _zqadic_newton_iteration(rop_auxi, M, op, k, n, prec, ctx);
    zqadic_set(rop, rop_auxi, ctx);
    // FAIRE LES CLEARS
}

void zqadic_frobenius_substitution(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    if ((ctx -> type) == TEICHMULLER)
    {
        zqadic_t cache;
        zqadic_init2(cache, zqadic_prec(op), ctx);

        padic_poly_compose_pow(cache, op, 2, ctx -> pctx);
        // CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
        zqadic_reduce(cache, ctx);
        zqadic_set(rop, cache, ctx);

        zqadic_clear(cache);
    }
    else
    {
        zqadic_t frob;
        zqadic_t xp;
        padic_t one;
        slong p = fmpz_get_si(ctx -> p);
        zqadic_init2(frob, zqadic_prec(rop), ctx);
        zqadic_init2(xp, 1, ctx);
        padic_init2(one, 1);
        padic_one(one);

        padic_poly_set_coeff_padic(xp, p, one, ctx -> pctx);

        zqadic_newton_iteration(frob, ctx -> M, xp, 0, 1, zqadic_prec(rop), ctx);
        zqadic_composition(rop, op, frob, ctx);
        // printf("zqadic_frobenius_substitution exception : non implémenté.");
        // exit(-1);

        // FAIRE LES CLEARS
    }
}