#include "zqadic.h"

void _zqadic_artin_schreier_root(zqadic_t x, zqadic_t alpha, zqadic_t beta, zqadic_t gamma, zqadic_ctx_t ctx)
{
    slong N = padic_poly_prec(x);

    if (N == 1)
    {
        zqadic_t cache;

        zqadic_init2(cache, 1, ctx);

        zqadic_inv(cache, alpha, ctx);
        zqadic_mul(cache, gamma, cache, ctx);
        zqadic_neg(cache, cache, ctx);
        zqadic_inv_frobenius_substitution(cache, cache, ctx);
        zqadic_set(x, cache, ctx);

        zqadic_clear(cache);
    }
    else
    {
        slong Nr = (N >> 1) + (N & 1); // partie entière supérieure de N
        
        zqadic_t cache1, cache2; // Varialbes cache
        zqadic_t xr, gammar, Deltar; // x', gamma', \Delta'
        padic_t p, p_pow_Nr, p_pow_mNr; // p, P^{N'}, P^{-N'}

        zqadic_init2(xr, Nr, ctx);
        zqadic_init2(gammar, N - Nr, ctx);
        zqadic_init2(Deltar, N - Nr, ctx);
        zqadic_init2(cache1, N, ctx);
        zqadic_init2(cache2, N, ctx);
        padic_init2(p, N);
        padic_init2(p_pow_mNr, N);
        padic_init2(p_pow_Nr, N);

        padic_set_fmpz(p, ctx -> p, ctx -> pctx);
        padic_pow_si(p_pow_Nr, p, Nr, ctx -> pctx);
        padic_pow_si(p_pow_mNr, p, -Nr, ctx -> pctx);

        _zqadic_artin_schreier_root(xr, alpha, beta, gamma, ctx);
        zqadic_set(cache1, xr, ctx);
        zqadic_frobenius_substitution(cache2, cache1, ctx);
        zqadic_mul(cache2, alpha, cache2, ctx);
        zqadic_mul(cache1, beta, cache1, ctx);
        zqadic_add(cache2, cache1, cache2, ctx);
        zqadic_add(cache2, cache2, gamma, ctx);
        padic_poly_scalar_mul_padic(cache2, cache2, p_pow_mNr, ctx -> pctx); // cache2 contient gamma'
        zqadic_set(gammar, cache2, ctx);
        _zqadic_artin_schreier_root(Deltar, alpha, beta, gammar, ctx);
        zqadic_set(cache1, Deltar, ctx);
        padic_poly_scalar_mul_padic(cache1, cache1, p_pow_Nr, ctx -> pctx); // cache1 contient p^{N'}\Delta'
        zqadic_set(cache2, xr, ctx);
        zqadic_add(x, cache1, cache2, ctx);

        zqadic_clear(xr);
        zqadic_clear(gammar);
        zqadic_clear(Deltar);
        zqadic_clear(cache1);
        zqadic_clear(cache2);
        padic_clear(p);
        padic_clear(p_pow_Nr);
        padic_clear(p_pow_mNr);
    }
}

void zqadic_artin_schreier_root(zqadic_t x, zqadic_t alpha, zqadic_t beta, zqadic_t gamma, zqadic_ctx_t ctx)
{
    slong prec = zqadic_prec(x);

    zqadic_t x_auxi, alpha_auxi, beta_auxi, gamma_auxi;

    zqadic_init2(x_auxi, prec, ctx);
    zqadic_init2(alpha_auxi, prec, ctx);
    zqadic_init2(beta_auxi, prec, ctx);
    zqadic_init2(gamma_auxi, prec, ctx);

    zqadic_set(alpha_auxi, alpha, ctx);
    zqadic_set(beta_auxi, beta, ctx);
    zqadic_set(gamma_auxi, gamma, ctx);
    _zqadic_artin_schreier_root(x_auxi, alpha_auxi, beta_auxi, gamma_auxi, ctx);
    zqadic_set(x, x_auxi, ctx);

    zqadic_clear(x_auxi);
    zqadic_clear(alpha_auxi);
    zqadic_clear(beta_auxi);
    zqadic_clear(gamma_auxi);
}