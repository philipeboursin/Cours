#include "zqadic.h"

void _zqadic_padic_poly_evaluation(zqadic_t rop, padic_poly_t f, zqadic_t op2, zqadic_ctx_t ctx)
{
    slong deg = padic_poly_degree(f);
    
    if (deg <= 0) zqadic_set(rop, f, ctx);
    else
    {
        slong prec = zqadic_prec(rop);
        slong B = n_sqrt(deg); // Calcule \lfloor \sqrt{d} \rfloor
        if (B*B != deg) B += 1; // B contient \lceil \sqrt{d} \rceil

        padic_poly_t f_auxi;
        zqadic_t tab[B + 1];
        zqadic_t op2_auxi, rop_auxi, sum, cache, op2_pow_i, YB, YBj;
        padic_t a;

        padic_poly_init2(f_auxi, deg + 1, prec);
        zqadic_init2(op2_auxi, prec, ctx);
        zqadic_init2(rop_auxi, prec, ctx);
        zqadic_init2(sum, prec, ctx);
        zqadic_init2(cache, prec, ctx);
        zqadic_init2(op2_pow_i, prec, ctx);
        zqadic_init2(YB, prec, ctx);
        zqadic_init2(YBj, prec, ctx);
        padic_init2(a, prec);

        padic_poly_set(f_auxi, f, ctx -> pctx); // Pour monter f à la bonne précision.
        zqadic_set(op2_auxi, op2, ctx); // Pour monter op2 à la bonne précision
        zqadic_one(op2_pow_i); // Contiendra op2^i
        zqadic_one(YBj);
        zqadic_zero(rop);

        for (slong i = 0; i <= B; i++)
        {
            zqadic_init2(tab[i], prec, ctx);
            zqadic_set(tab[i], op2_pow_i, ctx);
            zqadic_mul(op2_pow_i, op2_pow_i, op2_auxi, ctx); // Calcule op2*(op2^i)
        }

        zqadic_set(YB, tab[B], ctx);

        slong r = deg % B;
        slong q = deg / B;
        if (r != 0) q++;

        for (slong j = 0; j <= q; j++)
        {
            zqadic_zero(sum);
            for (slong i = 0; (i + B*j <= deg) && (i < B); i ++)
            {
                padic_poly_get_coeff_padic(a, f_auxi, i + B*j, ctx -> pctx);
                zqadic_set_padic(cache, a, ctx);
                zqadic_mul(cache, cache, tab[i], ctx);
                zqadic_add(sum, sum, cache, ctx);
            }
            zqadic_mul(sum, sum, YBj, ctx);
            zqadic_mul(YBj, YBj, YB, ctx);
            zqadic_add(rop_auxi, rop_auxi, sum, ctx);
        }

        zqadic_set(rop, rop_auxi, ctx);

        padic_poly_clear(f_auxi);
        zqadic_clear(op2_auxi);
        zqadic_clear(rop_auxi);
        zqadic_clear(sum);
        zqadic_clear(cache);
        zqadic_clear(op2_pow_i);
        for (int i = 0; i <= B; i++) zqadic_clear(tab[i]);
        zqadic_clear(YB);
        zqadic_clear(YBj);
        padic_clear(a);
    }
}

void zqadic_padic_poly_evaluation(zqadic_t rop, padic_poly_t f, zqadic_t op2, zqadic_ctx_t ctx)
{
    slong prec = zqadic_prec(rop);

    zqadic_t rop_auxi, f_auxi, op2_auxi;

    zqadic_init2(rop_auxi, prec, ctx);
    padic_poly_init2(f_auxi, padic_poly_degree(f) + 1, prec);
    zqadic_init2(op2_auxi, prec, ctx);

    padic_poly_set(f_auxi, f, ctx -> pctx);
    zqadic_set(op2_auxi, op2, ctx);
    _zqadic_padic_poly_evaluation(rop_auxi, f_auxi, op2_auxi, ctx);
    zqadic_set(rop, rop_auxi, ctx);

    zqadic_clear(rop_auxi);
    padic_poly_clear(f_auxi);
    zqadic_clear(op2_auxi);
}