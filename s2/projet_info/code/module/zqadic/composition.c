#include "zqadic.h"


void zqadic_composition(zqadic_t rop, zqadic_t op1, zqadic_t op2, zqadic_ctx_t ctx)
{
    slong prec = zqadic_prec(rop);
    slong deg = ctx -> deg;
    slong B = n_sqrt(deg); // Calcule \lfloor \sqrt{d} \rfloor
    if (B*B != deg) B += 1; // B contient \lceil \sqrt{d} \rceil

    zqadic_t op1_auxi;
    zqadic_t op2_auxi;
    zqadic_t rop_auxi;
    zqadic_t sum;
    zqadic_t cache;
    zqadic_t op2_pow_i;
    zqadic_t tab[B + 1];
    padic_t a;

    zqadic_init2(op1_auxi, prec, ctx);
    zqadic_init2(op2_auxi, prec, ctx);
    zqadic_init2(rop_auxi, prec, ctx);
    zqadic_init2(cache, prec, ctx);
    zqadic_init2(sum, prec, ctx);
    zqadic_init2(op2_pow_i, prec, ctx);
    zqadic_set(op1_auxi, op1, ctx); // Pour monter op1 à la bonne précision.
    zqadic_set(op2_auxi, op2, ctx); // Pour monter op2 à la bonne précision
    zqadic_one(op2_pow_i); // Contiendra op2^i
    zqadic_zero(rop);
    padic_init2(a, prec);

    for (slong i = 0; i <= B; i++)
    {
        zqadic_init2(tab[i], prec, ctx);
        zqadic_set(tab[i], op2_pow_i, ctx);
        zqadic_mul(op2_pow_i, op2_pow_i, op2_auxi, ctx); // Calcule op2*(op2^i)
    }

    // for (slong i = 0; i <= B; i++)
    // {
    //     zqadic_print(tab[i], ctx);
    //     printf("\n");
    // }

    slong r = deg % B;
    slong q = deg / B;
    if (r != 0) q++;

    for (slong j = 0; j < q; j++)
    {
        zqadic_zero(sum);
        for (slong i = 0; i + B*j < deg; i ++)
        {
            padic_poly_get_coeff_padic(a, op1_auxi, i + B*j, ctx -> pctx);
            // padic_print(a, ctx -> pctx);
            // printf("\n");
            zqadic_set_padic(cache, a, ctx);
            zqadic_mul(cache, cache, tab[i], ctx);
            zqadic_add(sum, sum, cache, ctx);
        }
        zqadic_mul(sum, sum, tab[B*j], ctx);
        zqadic_add(rop_auxi, rop_auxi, sum, ctx);
    }

    zqadic_set(rop, rop_auxi, ctx);

    // FAIRE LES CLEARS
}