#include "n2adic.h"

void _n2adic_inv_auxi(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx)
{
    int N = padic_poly_prec(rop);
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
        padic_poly_get_fmpz_poly(inter, ctx -> M, ctx -> pctx);
        fmpz_mod_poly_init(m, mod2_ctx);
        fmpz_mod_poly_set_fmpz_poly(m, inter, mod2_ctx);

        fq_ctx_init_modulus(fq_ctx, m, mod2_ctx, "x");

        n2adic_get_fmpz_poly(inter, op, ctx);
        fq_init(a, fq_ctx);
        fq_set_fmpz_poly(a, inter, fq_ctx);
        
        fq_init(inv_a, fq_ctx);
        fq_inv(inv_a, a, fq_ctx);

        fq_get_fmpz_poly(inter, inv_a, fq_ctx);
        n2adic_set_fmpz_poly(rop, inter, ctx);

        fq_clear(inv_a, fq_ctx);
        fq_clear(a, fq_ctx);
        fq_ctx_clear(fq_ctx);
        fmpz_mod_poly_clear(m, mod2_ctx);
        fmpz_mod_ctx_clear(mod2_ctx);
        fmpz_poly_clear(inter);
        fmpz_clear(deux);
    }
    else
    {
        int Nr = (N >> 1) + (N & 1);
        n2adic_t rop_mod_pNr;
        n2adic_t cache1;
        n2adic_t cache2;
        n2adic_t un;

        n2adic_init2(rop_mod_pNr, Nr, ctx);

        n2adic_init2(cache1, N, ctx);
        n2adic_init2(cache2, N, ctx);
        n2adic_init2(un, N, ctx);
        n2adic_one(un);

        _n2adic_inv_auxi(rop_mod_pNr, op, ctx);
        n2adic_set(cache1, rop_mod_pNr, ctx);
        n2adic_set(cache2, op, ctx);
        
        n2adic_mul(cache2, cache1, cache2, ctx); // rop*op dans cache2
        n2adic_reduce(cache2, ctx);
        n2adic_sub(cache2, un, cache2,ctx); // 1 - rop*op dans cache2
        n2adic_mul(cache2, cache1, cache2,ctx); // rop*(1 - rop*op) dans cache2
        n2adic_add(cache2, cache1, cache2,ctx); // rop - rop*(1 - rop*op) dans cache2
        n2adic_reduce(cache2, ctx);
        n2adic_set(rop, cache2, ctx); //
        
        n2adic_clear(rop_mod_pNr);
        n2adic_clear(cache1);
        n2adic_clear(cache2);
        n2adic_clear(un);
    }
}

// Inverse op et met le résultat dans rop. Supporte l'aliasing
void n2adic_inv(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx)
{
    if (n2adic_val(op) != 0)
    {
        printf("n2adic_inv exception : op n'est pas inversible.\n");
        exit(-1);
    }
    else
    {
        n2adic_t auxi;
        n2adic_init(auxi, n2adic_ctx);

        _n2adic_inv_auxi(auxi, op, n2adic_ctx);

        n2adic_set(rop, auxi, n2adic_ctx);
        n2adic_clear(auxi);
    }
}