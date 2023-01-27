#include "n2adic.h"

// void artin_schreier_root(n2adic_t x, n2adic_t alpha, n2adic_t beta, n2adic_t gamma, n2adic_ctx_t ctx)
// {
//     int prec = n2adic_prec(x);
//     padic_poly_t x_auxi;
//     padic_poly_t alpha_auxi;
//     padic_poly_t beta_auxi;
//     padic_poly_t gamma_auxi;

//     padic_poly_init2(x_auxi, padic_poly_degree(x), prec);
//     padic_poly_init2(alpha_auxi, padic_poly_degree(alpha), prec);
//     padic_poly_init2(beta_auxi, padic_poly_degree(beta), prec);
//     padic_poly_init2(gamma_auxi, padic_poly_degree(gamma), prec);

//     padic_poly_set(alpha_auxi, alpha);
//     padic_poly_set(beta_auxi, beta);
//     padic_poly_set(gamma_auxi, gamma);

//     _artin_schreier_root_auxi(x_auxi, alpha_auxi, beta_auxi, gamma_auxi, ctx);

//     n2adic_set_padic_poly(x, x_auxi, ctx);

//     // FAIRE LES CLEARS
// }

// void _artin_schreier_root_auxi(padic_poly_t x, padic_poly_t alpha, padic_poly_t beta, padic_poly_t gamma, padic_poly_t M, n2adic_ctx_t ctx)
// {
//     int prec = padic_poly_prec(M);
//     if (prec == 1)
//     {
//         fmpz_t deux;
//         fmpz_poly_t inter;
//         fmpz_mod_poly_t m;
//         fq_ctx_t fq_ctx;
//         fmpz_mod_ctx_t mod2_ctx;
        
//         fq_t alpha1;
//         fq_t gamma1;

//         fmpz_poly_init(inter);
//         fmpz_init_set_ui(deux, 2);
//         fmpz_mod_ctx_init(mod2_ctx, deux);
//         fmpz_mod_poly_init(m, mod2_ctx);
//         padic_poly_get_fmpz_poly(inter, M, ctx -> ctx);
//         fmpz_mod_poly_set_fmpz_poly(m, inter, mod2_ctx);
//         fq_ctx_init_modulus(fq_ctx, m, mod2_ctx, "x"); // Contexte F_{2^d} initialisé

//         fq_init(alpha1, fq_ctx);
//         fq_init(gamma1, fq_ctx);

//         padic_poly_get_fmpz_poly(inter, alpha, ctx -> ctx);
//         fq_set_fmpz_poly(alpha1, inter, fq_ctx);

//         padic_poly_get_fmpz_poly(inter, gamma, ctx -> ctx);
//         fq_set_fmpz_poly(gamma1, inter, fq_ctx);

//         fq_neg(gamma1, gamma1, fq_ctx);
//         fq_inv(alpha1, alpha1, fq_ctx);
//         fq_mul(alpha1, alpga1, gamma1, fq_ctx);
//         fq_pth_root(alpha1, alpha1, fq_ctx);

//         fq_get_fmpz_poly(inter, alpha1, fq_ctx);
//         padic_poly_set_fmpz_poly(x, inter, ctx -> ctx);

//         // FAIRE LES CLEARS
//     }
//     else
//     {
//         int Nr = (N >> 1) + (N & 1);

//     }
// }