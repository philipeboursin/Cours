#include "zqadic.h"

void _zqadic_artin_schreier_root_auxi(zqadic_t x, zqadic_t alpha, zqadic_t beta, zqadic_t gamma, zqadic_ctx_t ctx)
{
    slong N = padic_poly_prec(x);

    if (N == 1)
    {
        fmpz_t deux;
        fmpz_poly_t inter;
        fmpz_mod_ctx_t mod2_ctx;
        fmpz_mod_poly_t m;
        fq_ctx_t fq_ctx;
        fq_t alpha1;
        fq_t gamma1;

        fmpz_poly_init(inter);
        fmpz_init_set_ui(deux, 2);
        fmpz_mod_ctx_init(mod2_ctx, deux);
        fmpz_mod_poly_init(m, mod2_ctx);
        padic_poly_get_fmpz_poly(inter, ctx -> M, ctx -> pctx);
        fmpz_mod_poly_set_fmpz_poly(m, inter, mod2_ctx);
        fq_ctx_init_modulus(fq_ctx, m, mod2_ctx, "x"); // Contexte F_{2^d} initialisé

        fq_init(alpha1, fq_ctx);
        fq_init(gamma1, fq_ctx);

        zqadic_get_fmpz_poly(inter, alpha, ctx);
        fq_set_fmpz_poly(alpha1, inter, fq_ctx);

        zqadic_get_fmpz_poly(inter, gamma, ctx);
        fq_set_fmpz_poly(gamma1, inter, fq_ctx);

        fq_neg(gamma1, gamma1, fq_ctx);
        fq_inv(alpha1, alpha1, fq_ctx);
        fq_mul(alpha1, alpha1, gamma1, fq_ctx);
        fq_pth_root(alpha1, alpha1, fq_ctx);

        fq_get_fmpz_poly(inter, alpha1, fq_ctx);
        zqadic_set_fmpz_poly(x, inter, ctx);

        fq_clear(alpha1, fq_ctx);
        fq_clear(gamma1, fq_ctx);
        fq_ctx_clear(fq_ctx);
        fmpz_mod_poly_clear(m, mod2_ctx);
        fmpz_mod_ctx_clear(mod2_ctx);
        fmpz_poly_clear(inter);
        fmpz_clear(deux);
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