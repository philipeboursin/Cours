#include "zqadic.h"

void _zqadic_inv_auxi(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    int N = padic_poly_prec(rop);
    if (N == 1)
    {
        fmpz_poly_t inter; // variable cache pour stocker un polybnôme à coefficient entiers (fait le pont entre les corps finis et les qadiques)
        fmpz_mod_poly_t m; // réduction modulo 2 de inter (même si ses coefficients sont déjà 0 ou 1 vu la précision de op)
        fq_ctx_t fq_ctx; // Contexte F_2^d défini par M
        fmpz_mod_ctx_t mod2_ctx; // Contexte des entiers modulo 2
        fq_t a; // op vu comme un élément de Fq
        fq_t inv_a; // l'inverse de a

        fmpz_mod_ctx_init(mod2_ctx, ctx -> p);
        fmpz_poly_init(inter);
        padic_poly_get_fmpz_poly(inter, ctx -> M, ctx -> pctx);
        fmpz_mod_poly_init(m, mod2_ctx);
        fmpz_mod_poly_set_fmpz_poly(m, inter, mod2_ctx);

        fq_ctx_init_modulus(fq_ctx, m, mod2_ctx, "x");

        zqadic_get_fmpz_poly(inter, op, ctx);
        fq_init(a, fq_ctx);
        fq_set_fmpz_poly(a, inter, fq_ctx);
        
        fq_init(inv_a, fq_ctx);
        fq_inv(inv_a, a, fq_ctx);

        fq_get_fmpz_poly(inter, inv_a, fq_ctx);
        zqadic_set_fmpz_poly(rop, inter, ctx);

        fq_clear(inv_a, fq_ctx);
        fq_clear(a, fq_ctx);
        fq_ctx_clear(fq_ctx);
        fmpz_mod_poly_clear(m, mod2_ctx);
        fmpz_mod_ctx_clear(mod2_ctx);
        fmpz_poly_clear(inter);
    }
    else
    {
        int Nr = (N >> 1) + (N & 1);
        zqadic_t rop_mod_pNr;
        zqadic_t cache1;
        zqadic_t cache2;
        zqadic_t un;

        zqadic_init2(rop_mod_pNr, Nr, ctx);

        zqadic_init2(cache1, N, ctx);
        zqadic_init2(cache2, N, ctx);
        zqadic_init2(un, N, ctx);
        zqadic_one(un);

        _zqadic_inv_auxi(rop_mod_pNr, op, ctx);
        zqadic_set(cache1, rop_mod_pNr, ctx);
        zqadic_set(cache2, op, ctx);
        
        zqadic_mul(cache2, cache1, cache2, ctx); // rop*op dans cache2
        zqadic_reduce(cache2, ctx);
        zqadic_sub(cache2, un, cache2,ctx); // 1 - rop*op dans cache2
        zqadic_mul(cache2, cache1, cache2,ctx); // rop*(1 - rop*op) dans cache2
        zqadic_add(cache2, cache1, cache2,ctx); // rop - rop*(1 - rop*op) dans cache2
        zqadic_reduce(cache2, ctx);
        zqadic_set(rop, cache2, ctx); //
        
        zqadic_clear(rop_mod_pNr);
        zqadic_clear(cache1);
        zqadic_clear(cache2);
        zqadic_clear(un);
    }
}

// Inverse op et met le résultat dans rop. Supporte l'aliasing
void zqadic_inv(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    if (zqadic_val(op) != 0)
    {
        printf("zqadic_inv exception : op n'est pas inversible.\n");
        exit(-1);
    }
    else
    {
        slong N = zqadic_prec(rop);
        zqadic_t rop_auxi;
        zqadic_t op_auxi;

        zqadic_init2(rop_auxi, N, ctx);
        zqadic_init2(op_auxi, N, ctx);

        zqadic_set(op_auxi, op, ctx);
        _zqadic_inv_auxi(rop_auxi, op_auxi, ctx);
        zqadic_set(rop, rop_auxi, ctx);

        zqadic_clear(rop_auxi);
        zqadic_clear(op_auxi);
    }
}