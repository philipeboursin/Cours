#include "zqadic.h"

void _zqadic_artin_schreier_root_auxi(zqadic_t x, zqadic_t alpha, zqadic_t beta, zqadic_t gamma, zqadic_ctx_t ctx)
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
        slong Nr = (N >> 1) + (N & 1); // Nr contient N' la partie entière supérieure de N
        zqadic_t xr;
        zqadic_t gammar;
        zqadic_t Deltar;
        zqadic_t cache1;
        zqadic_t cache2;
        padic_t deux;
        padic_t deux_pow_Nr;
        padic_t deux_pow_mNr;

        zqadic_init2(xr, Nr, ctx);
        zqadic_init2(gammar, N - Nr, ctx);
        zqadic_init2(Deltar, N - Nr, ctx);
        zqadic_init2(cache1, N, ctx);
        zqadic_init2(cache2, N, ctx);
        padic_init2(deux, N);
        padic_init2(deux_pow_mNr, N);
        padic_init2(deux_pow_Nr, N);
        padic_set_ui(deux, 2, ctx -> pctx);
        padic_pow_si(deux_pow_Nr, deux, Nr, ctx -> pctx); // deux_pow_Nr contient 2^{N'}
        padic_pow_si(deux_pow_mNr, deux, -Nr, ctx -> pctx); // deux_pow_mNr contient 2^{-N'}

        _zqadic_artin_schreier_root_auxi(xr, alpha, beta, gamma, ctx);
        zqadic_set(cache1, xr, ctx); // cache1 contient x', à précision N

        // printf("N = %ld\n", N);
        // printf("cache 1 = ");
        // zqadic_print(cache1, ctx);
        // printf("\n");
        
        zqadic_frobenius_substitution(cache2, cache1, ctx);
        zqadic_mul(cache2, alpha, cache2, ctx); // cache2 contient \alpha \Sigma(x')
        zqadic_mul(cache1, beta, cache1, ctx); // cache1 contient \beta x'
        zqadic_add(cache2, cache1, cache2, ctx); // cache2 contient \alpha \Sigma(x') + \beta x'
        zqadic_add(cache2, cache2, gamma, ctx); // cache2 contient \alpha \Sigma(x') + \beta x' + \gamma
        padic_poly_scalar_mul_padic(cache2, cache2, deux_pow_mNr, ctx -> pctx); // cache 2 contient gamma'
        zqadic_set(gammar, cache2, ctx);
        _zqadic_artin_schreier_root_auxi(Deltar, alpha, beta, gammar, ctx);
        zqadic_set(cache1, Deltar, ctx);
        padic_poly_scalar_mul_padic(cache1, cache1, deux_pow_Nr, ctx -> pctx); // cache 2 contient gamma'
        zqadic_set(cache2, xr, ctx);
        zqadic_add(x, cache1, cache2, ctx);

        zqadic_clear(xr);
        zqadic_clear(gammar);
        zqadic_clear(Deltar);
        zqadic_clear(cache1);
        zqadic_clear(cache2);
        padic_clear(deux);
        padic_clear(deux_pow_Nr);
        padic_clear(deux_pow_mNr);
    }
}

void zqadic_artin_schreier_root(zqadic_t x, zqadic_t alpha, zqadic_t beta, zqadic_t gamma, zqadic_ctx_t ctx)
{

    slong prec = zqadic_prec(x);
    zqadic_t x_auxi;

    zqadic_init2(x_auxi, prec, ctx);
    _zqadic_artin_schreier_root_auxi(x_auxi, alpha, beta, gamma, ctx);
    zqadic_set(x, x_auxi, ctx);

    zqadic_clear(x_auxi);
}