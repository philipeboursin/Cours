#include "n2adic.h"

void _n2adic_inv_auxi(padic_poly_t rop, padic_poly_t op, padic_poly_t M, n2adic_ctx_t ctx)
{
    int N = padic_poly_prec(M);

    if (N == 1)
    {
        fmpz_t deux;
        fmpz_poly_t inter; // variable cache pour stocker un polybnôme à coefficient entiers (fait le pont entre les corps finis et les qadiques)
        fmpz_mod_poly_t m; // réduction modulo 2 de inter (même si ses coefficients sont déjà 0 ou 1 vu la précision de op)
        fq_ctx_t fq_ctx; // Contexte F_2^d défini par M
        fmpz_mod_ctx_t mod2_ctx; // Contexte des entiers modulo 2
        fq_t a; // op vu comme un élément de Fq
        fq_t inv_a; // l'inverse de a


        fmpz_init_set_ui(deux, 2);
        fmpz_mod_ctx_init(mod2_ctx, deux);
        fmpz_poly_init(inter);
        padic_poly_get_fmpz_poly(inter, M, ctx->ctx);
        fmpz_mod_poly_init(m, mod2_ctx);
        fmpz_mod_poly_set_fmpz_poly(m, inter, mod2_ctx);

        fq_ctx_init_modulus(fq_ctx, m, mod2_ctx, "x");

        padic_poly_get_fmpz_poly(inter, op, ctx->ctx);
        fq_init(a, fq_ctx);
        fq_set_fmpz_poly(a, inter, fq_ctx);
        

        fq_init(inv_a, fq_ctx);
        fq_inv(inv_a, a, fq_ctx);


        fq_get_fmpz_poly(inter, inv_a, fq_ctx);
        padic_poly_set_fmpz_poly(rop, inter, ctx->ctx);

        //------ FAIRE LES CLEARS
    }
    else
    {
        int Nr = (N >> 1) + (N & 1);
        padic_poly_t rop_mod_pNr;
        padic_poly_t M_mod_pNr;
        padic_poly_t op_mod_pNr;
        padic_poly_t cache1;
        padic_poly_t cache2;
        padic_poly_t cache3;
        padic_poly_t un;

        padic_poly_init2(rop_mod_pNr, 0, Nr);
        padic_poly_init2(op_mod_pNr, 0, Nr);
        padic_poly_init2(M_mod_pNr, 0, Nr);

        padic_poly_init2(cache1, 0, N);
        padic_poly_init2(cache2, 0, N);
        padic_poly_init2(cache3, 0, N);
        padic_poly_init2(un, 0, N);
        padic_poly_one(un);

        padic_poly_set(op_mod_pNr, op, ctx->ctx);
        padic_poly_set(M_mod_pNr, M, ctx->ctx);

        _n2adic_inv_auxi(rop_mod_pNr, op, M_mod_pNr, ctx);
        padic_poly_set(cache1, rop_mod_pNr, ctx->ctx);
        padic_poly_set(cache2, op, ctx->ctx);
        
        // printf("cache1 = ");
        // n2adic_print(cache1, ctx);
        // printf("\n");
        
        // printf("cache2 = ");
        // n2adic_print(cache2, ctx);
        // printf("\n");
        
        padic_poly_mul(cache2, cache1, cache2, ctx->ctx); // rop*op dans cache2
        _padic_poly_div_eucl(cache2, M, cache2, cache3, ctx->ctx);
        padic_poly_sub(cache2, un, cache2, ctx->ctx); // 1 - rop*op dans cache2
        padic_poly_mul(cache2, cache1, cache2, ctx->ctx); // rop*(1 - rop*op) dans cache2
        padic_poly_add(cache2, cache1, cache2, ctx->ctx); // rop - rop*(1 - rop*op) dans cache2
        _padic_poly_div_eucl(cache2, M, cache2, cache3, ctx->ctx);
        padic_poly_set(rop, cache2, ctx->ctx); //
        

        //------ FAIRE LES CLEARS
    }

        // printf("rop = ");
        // padic_poly_print(rop, ctx->ctx);
        // printf("\n");
}

// Inverse op et met le résultat dans rop. Supporte l'aliasing
void n2adic_inv(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx)
{
    n2adic_t auxi;
    n2adic_init(auxi, n2adic_ctx);

    _n2adic_inv_auxi(auxi, op, n2adic_ctx -> M, n2adic_ctx);

    n2adic_set(rop, auxi, n2adic_ctx);
}