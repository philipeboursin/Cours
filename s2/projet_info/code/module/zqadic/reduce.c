#include "zqadic.h"

void _padic_poly_newton_inv(padic_poly_t rop, padic_poly_t op, slong n, padic_ctx_t ctx)
{
    if (n == 1) padic_poly_one(rop);
    else
    {
        slong prec = padic_poly_prec(op);
        slong nr = (n >> 1) + (n & 1);
        
        padic_poly_t cache, un;

        padic_poly_init2(cache, 0, prec);
        padic_poly_init2(un, 1, prec);

        padic_poly_one(un);
        _padic_poly_newton_inv(rop, op, nr, ctx);
        padic_poly_mul(cache, rop, op, ctx);
        _padic_poly_set_length(cache, n + 1);
        padic_poly_sub(cache, un, cache, ctx);
        padic_poly_mul(cache, rop, cache, ctx);
        _padic_poly_set_length(cache, n + 1);
        padic_poly_add(cache, cache, rop, ctx);
        _padic_poly_set_length(cache, n + 1);
        padic_poly_set(rop, cache, ctx);

        padic_poly_clear(cache);
        padic_poly_clear(un);
    }
}

void padic_poly_newton_inv(padic_poly_t rop, padic_poly_t op, slong n, padic_ctx_t ctx)
{
    padic_poly_t auxi;

    padic_poly_init2(auxi, 0, padic_poly_prec(op));
    
    _padic_poly_newton_inv(auxi, op, n, ctx);
    padic_poly_set(rop, auxi, ctx);
    
    padic_poly_clear(auxi);
}

void padic_poly_symetric(padic_poly_t P, padic_poly_t Q, padic_ctx_t C)
{
    slong deg = padic_poly_degree(Q);
    slong N = padic_poly_prec(Q);

    padic_poly_t R;
    padic_t padic_cache;

    padic_poly_init2(R, deg + 1, N);
    padic_init2(padic_cache, N);

    for (slong i = 0; i < deg + 1; i++)
    {
        padic_poly_get_coeff_padic(padic_cache, Q, i, C);
        padic_poly_set_coeff_padic(R, deg - i, padic_cache, C);
    }
    padic_poly_set(P, R, C);

    padic_poly_clear(R);
    padic_clear(padic_cache);
}

void _padic_poly_eucl_div(padic_poly_t R, padic_poly_t Q, padic_poly_t A, padic_poly_t B, padic_ctx_t C)
{
    slong degA = padic_poly_degree(A);
    slong degB = padic_poly_degree(B);
    slong N = padic_poly_prec(B);

    if (degA < degB)
    {
        padic_poly_set(R, A, C);
        padic_poly_zero(Q);
    }
    else
    {
        slong n = degA - degB + 1;

        padic_poly_t P1, P2; //polynômes variables caches

        padic_poly_init2(P1, degA, N);
        padic_poly_init2(P2, degA, N);

        padic_poly_symetric(P2, B, C);
        // padic_poly_inv_series(P2, P2, n, C); // Ne fonctionne pas pour une raison inconnue (bug dans flint)
        padic_poly_newton_inv(P2, P2, n, C);
        padic_poly_symetric(P1, A, C);
        padic_poly_mul(P2, P1, P2, C);
        _padic_poly_set_length(P2, n);
        padic_poly_symetric(Q, P2, C);  
        padic_poly_mul(P1, B, Q, C);
        padic_poly_sub(R, A, P1, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);
    }
}

void padic_poly_eucl_div(padic_poly_t R, padic_poly_t Q, padic_poly_t A, padic_poly_t B, padic_ctx_t ctx)
{
    slong prec = padic_poly_prec(R);

    padic_poly_t R_auxi, Q_auxi, A_auxi, B_auxi;

    padic_poly_init2(R_auxi, 0, prec);
    padic_poly_init2(Q_auxi, 0, prec);
    padic_poly_init2(A_auxi, 0, prec);
    padic_poly_init2(B_auxi, 0, prec);

    padic_poly_set(A_auxi, A, ctx);
    padic_poly_set(B_auxi, B, ctx);
    _padic_poly_eucl_div(R_auxi, Q_auxi, A_auxi, B_auxi, ctx);
    padic_poly_set(R, R_auxi, ctx);
    padic_poly_set(Q, Q_auxi, ctx);

    padic_poly_clear(R_auxi);
    padic_poly_clear(Q_auxi);
    padic_poly_clear(A_auxi);
    padic_poly_clear(B_auxi);
}   

void zqadic_reduce(zqadic_t x, zqadic_ctx_t ctx)
{
    slong prec = padic_poly_prec(x);

    zqadic_t y;
    padic_poly_t Mprec;

    zqadic_init2(y, prec, ctx);
    padic_poly_init2(Mprec, (ctx -> deg) + 1, prec);
    padic_poly_set(Mprec, ctx -> M, ctx -> pctx);

    padic_poly_eucl_div(x, y, x, Mprec, ctx -> pctx);
    padic_poly_reduce(x, ctx -> pctx);

    padic_poly_clear(Mprec);
    zqadic_clear(y);
}