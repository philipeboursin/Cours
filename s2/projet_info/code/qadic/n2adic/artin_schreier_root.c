#include "n2adic.h"

void _n2adic_artin_schreier_root_auxi(n2adic_t x, n2adic_t alpha, n2adic_t beta, n2adic_t gamma, n2adic_ctx_t ctx)
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
        padic_poly_get_fmpz_poly(inter, ctx -> M, ctx -> ctx);
        fmpz_mod_poly_set_fmpz_poly(m, inter, mod2_ctx);
        fq_ctx_init_modulus(fq_ctx, m, mod2_ctx, "x"); // Contexte F_{2^d} initialisé

        fq_init(alpha1, fq_ctx);
        fq_init(gamma1, fq_ctx);

        n2adic_get_fmpz_poly(inter, alpha, ctx);
        fq_set_fmpz_poly(alpha1, inter, fq_ctx);

        n2adic_get_fmpz_poly(inter, gamma, ctx);
        fq_set_fmpz_poly(gamma1, inter, fq_ctx);

        fq_neg(gamma1, gamma1, fq_ctx);
        fq_inv(alpha1, alpha1, fq_ctx);
        fq_mul(alpha1, alpha1, gamma1, fq_ctx);
        fq_pth_root(alpha1, alpha1, fq_ctx);

        fq_get_fmpz_poly(inter, alpha1, fq_ctx);
        n2adic_set_fmpz_poly(x, inter, ctx);

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
        n2adic_t xr;
        n2adic_t gammar;
        n2adic_t Deltar;
        n2adic_t cache1;
        n2adic_t cache2;
        padic_t deux;
        padic_t deux_pow_Nr;
        padic_t deux_pow_mNr;

        n2adic_init2(xr, Nr, ctx);
        n2adic_init2(gammar, N - Nr, ctx);
        n2adic_init2(Deltar, N - Nr, ctx);
        n2adic_init2(cache1, N, ctx);
        n2adic_init2(cache2, N, ctx);
        padic_init2(deux, N);
        padic_init2(deux_pow_mNr, N);
        padic_init2(deux_pow_Nr, N);
        padic_set_ui(deux, 2, ctx -> ctx);
        padic_pow_si(deux_pow_Nr, deux, Nr, ctx -> ctx); // deux_pow_Nr contient 2^{N'}
        padic_pow_si(deux_pow_mNr, deux, -Nr, ctx -> ctx); // deux_pow_mNr contient 2^{-N'}

        _n2adic_artin_schreier_root_auxi(xr, alpha, beta, gamma, ctx);
        n2adic_set(cache1, xr, ctx); // cache1 contient x', à précision N
        n2adic_frobenius_substitution(cache2, cache1, ctx);
        n2adic_mul(cache2, alpha, cache2, ctx); // cache2 contient \alpha \Sigma(x')
        n2adic_mul(cache1, beta, cache1, ctx); // cache1 contient \beta x'
        n2adic_add(cache2, cache1, cache2, ctx); // cache2 contient \alpha \Sigma(x') + \beta x'
        n2adic_add(cache2, cache2, gamma, ctx); // cache2 contient \alpha \Sigma(x') + \beta x' + \gamma
        padic_poly_scalar_mul_padic(cache2, cache2, deux_pow_mNr, ctx -> ctx); // cache 2 contient gamma'
        n2adic_set(gammar, cache2, ctx);
        _n2adic_artin_schreier_root_auxi(Deltar, alpha, beta, gammar, ctx);
        n2adic_set(cache1, Deltar, ctx);
        padic_poly_scalar_mul_padic(cache1, cache1, deux_pow_Nr, ctx -> ctx); // cache 2 contient gamma'
        n2adic_set(cache2, xr, ctx);
        n2adic_add(x, cache1, cache2, ctx);

        n2adic_clear(xr);
        n2adic_clear(gammar);
        n2adic_clear(Deltar);
        n2adic_clear(cache1);
        n2adic_clear(cache2);
        padic_clear(deux);
        padic_clear(deux_pow_Nr);
        padic_clear(deux_pow_mNr);
    }
}

void n2adic_artin_schreier_root(n2adic_t x, n2adic_t alpha, n2adic_t beta, n2adic_t gamma, n2adic_ctx_t ctx)
{
    slong prec = n2adic_prec(x);
    n2adic_t x_auxi;

    n2adic_init2(x_auxi, prec, ctx);
    _n2adic_artin_schreier_root_auxi(x_auxi, alpha, beta, gamma, ctx);
    n2adic_set(x, x_auxi, ctx);

    n2adic_clear(x_auxi);
}