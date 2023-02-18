#include "zqadic.h"

// Ne fonctionne qu'avec k = 0 pour le moment. N + k est donné par la précition de rop, et n + k par la précision de op. M est aussi à précision N + k.
void _zqadic_newton_iteration(zqadic_t rop, padic_poly_t M, zqadic_t op, slong k, zqadic_ctx_t ctx)
{
    slong Npk = zqadic_prec(rop); // N + k

    if (Npk <= zqadic_prec(op)) // équivalent à N <= n, zqadic_prec(op) = n + k
    {
        zqadic_set(rop, op, ctx);
    }
    else
    {
        slong Nr = (Npk >> 1) + (Npk & 1); // \lceil (N + k)/2 \rceil
        slong Npkr = Nr + k;

        zqadic_t ropr;
        zqadic_t z;
        zqadic_t Mz;
        zqadic_t Mrz;
        padic_poly_t M_auxi;
        padic_poly_t Mr;

        zqadic_init2(ropr, Npkr, ctx);
        zqadic_init2(z, Npk, ctx);
        zqadic_init2(Mz, Npk, ctx);
        zqadic_init2(Mrz, Npkr, ctx);
        padic_poly_init2(M_auxi, (ctx -> deg) + 1, Npkr);
        padic_poly_init2(Mr, ctx -> deg, Npk);

        padic_poly_set(M_auxi, M, ctx -> pctx);
        padic_poly_derivative(Mr, M, ctx -> pctx);
        _zqadic_newton_iteration(ropr, M_auxi, op, k, ctx);
        zqadic_set(z, ropr, ctx);
                
        // printf("M = ");
        // zqadic_print(M, ctx);
        // printf("\n");

        zqadic_padic_poly_evaluation(Mz, M, z, ctx);
        // printf("f(z) = ");
        // zqadic_print(Mz, ctx);
        // printf("\n");
        zqadic_padic_poly_evaluation(Mrz, Mr, ropr, ctx);
        zqadic_inv(Mrz, Mrz, ctx);
        zqadic_mul(rop, Mrz, Mz, ctx);
        zqadic_sub(rop, z, rop, ctx);

        zqadic_clear(ropr);
        zqadic_clear(z);
        zqadic_clear(Mz);
        zqadic_clear(Mrz);
        padic_poly_clear(M_auxi);
        padic_poly_clear(Mr);
    }
}

// Précision de rop : N + k
void zqadic_newton_iteration(zqadic_t rop, padic_poly_t M, zqadic_t op, slong k, zqadic_ctx_t ctx)
{
    slong Npk = zqadic_prec(rop);

    zqadic_t rop_auxi;
    padic_poly_t M_auxi;

    zqadic_init2(rop_auxi, Npk, ctx);
    padic_poly_init2(M_auxi, (ctx -> deg) + 1, Npk);

    padic_poly_set(M_auxi, M, ctx -> pctx);
    _zqadic_newton_iteration(rop_auxi, M_auxi, op, k, ctx);
    zqadic_set(rop, rop_auxi, ctx);

   zqadic_clear(rop_auxi);
   padic_poly_clear(M_auxi);
}

void _zqadic_frobenius_substitution(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    if ((ctx -> type) == TEICHMULLER)
    {
        zqadic_t cache;
        zqadic_init2(cache, zqadic_prec(op), ctx);

        padic_poly_compose_pow(cache, op, 2, ctx -> pctx);
        // CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
        zqadic_reduce(cache, ctx);
        zqadic_set(rop, cache, ctx);

        zqadic_clear(cache);
    }
    else
    {
        zqadic_t frob;
        zqadic_t xp;
        padic_t one;
        slong p = fmpz_get_si(ctx -> p);
        zqadic_init2(frob, zqadic_prec(rop), ctx);
        zqadic_init2(xp, 1, ctx);
        padic_init2(one, 1);
        padic_one(one);

        padic_poly_set_coeff_padic(xp, p, one, ctx -> pctx);

        //
        // padic_poly_t Mr;
        // padic_poly_init2(Mr, 0, ctx -> prec);
        // padic_poly_derivative(Mr, ctx -> M, ctx -> pctx);
        // zqadic_padic_poly_evaluation(Mr, Mr, xp, ctx);
        // printf("v(f'(a)) = %ld\n f'(a) = ", zqadic_val(Mr));
        // padic_poly_print(Mr, ctx -> pctx);
        // printf("\n");
        // //

        // printf("X^p = ");
        // zqadic_print(xp, ctx);
        // printf("\n");

        zqadic_newton_iteration(frob, ctx -> M, xp, 0, ctx);
        // printf("Sigma(X) = ");
        // zqadic_print(frob , ctx);
        // printf("\n");
        zqadic_padic_poly_evaluation(rop, op, frob, ctx);
        // printf("zqadic_frobenius_substitution exception : non implémenté.");
        // exit(-1);

        zqadic_clear(frob);
        zqadic_clear(xp);
        padic_clear(one);
    }
}

void zqadic_frobenius_substitution(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    slong prec = zqadic_prec(rop);
    zqadic_t rop_auxi;
    zqadic_t op_auxi;

    zqadic_init2(rop_auxi, prec, ctx);
    zqadic_init2(op_auxi, prec, ctx);

    zqadic_set(op_auxi, op, ctx);
    _zqadic_frobenius_substitution(rop_auxi, op_auxi, ctx);

    zqadic_set(rop, rop_auxi, ctx);

    zqadic_clear(rop_auxi);
    zqadic_clear(op_auxi);
}