#include "zqadic.h"

void _padic_poly_newton_inv_auxi(padic_poly_t rop, padic_poly_t op, int n, padic_ctx_t ctx)
{
    if (n == 1)
    {
        padic_poly_one(rop);
    }
    else
    {
        int prec = padic_poly_prec(op);
        
        padic_poly_t cache;
        padic_poly_t un;

        padic_poly_init2(cache, 0, prec);
        padic_poly_init2(un, 1, prec);
        padic_poly_one(un);

        int nr = (n >> 1) + (n & 1);
        _padic_poly_newton_inv_auxi(rop, op, nr, ctx);
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

void _padic_poly_newton_inv(padic_poly_t rop, padic_poly_t op, int n, padic_ctx_t ctx)
{
    padic_poly_t auxi;
    padic_poly_init2(auxi, 0, padic_poly_prec(op));
    _padic_poly_newton_inv_auxi(auxi, op, n, ctx);
    padic_poly_set(rop, auxi, ctx);
    padic_poly_clear(auxi);
}

void _coeff_symetry(padic_poly_t P, padic_poly_t Q, padic_ctx_t C) // Procédure qui transforme P en un polynôme dont les coefficients sont ceux de Q renversés. Supporte l'aliasing
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

// Ne fonctionne que si B est unitaire
void __padic_poly_div_eucl_auxi(padic_poly_t R, padic_poly_t Q, padic_poly_t A, padic_poly_t B, padic_ctx_t C)
{
    int degA = padic_poly_degree(A);
    int degB = padic_poly_degree(B);
    int N = padic_poly_prec(B);

    if (degA < degB)
    {
        padic_poly_set(R, A, C);
        padic_poly_zero(Q);
    }
    else
    {
        int n = degA - degB + 1;

        padic_poly_t P1; //polynômes variables caches
        padic_poly_t P2;

        padic_poly_init2(P1, degA, N);
        padic_poly_init2(P2, degA, N);

        _coeff_symetry(P2, B, C);
        // padic_poly_inv_series(P2, P2, n, C); // Ne fonctionne pas pour une raison inconnue
        _padic_poly_newton_inv(P2, P2, n, C);
        _coeff_symetry(P1, A, C);
        padic_poly_mul(P2, P1, P2, C);
        _padic_poly_set_length(P2, n);
        _coeff_symetry(Q, P2, C);  

        padic_poly_mul(P1, B, Q, C);
        padic_poly_sub(R, A, P1, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);
    }
}

// ne fonctionne qu'avec B unitaire
void _padic_poly_div_eucl(padic_poly_t R, padic_poly_t Q, padic_poly_t A, padic_poly_t B, padic_ctx_t ctx)
{
    slong prec = padic_poly_prec(R);
    padic_poly_t R_auxi, Q_auxi, A_auxi, B_auxi;

    padic_poly_init2(R_auxi, 0, prec);
    padic_poly_init2(Q_auxi, 0, prec);
    padic_poly_init2(A_auxi, 0, prec);
    padic_poly_init2(B_auxi, 0, prec);

    padic_poly_set(A_auxi, A, ctx);
    padic_poly_set(B_auxi, B, ctx);

    __padic_poly_div_eucl_auxi(R_auxi, Q_auxi, A_auxi, B_auxi, ctx);

    padic_poly_set(R, R_auxi, ctx);
    padic_poly_set(Q, Q_auxi, ctx);

    padic_poly_clear(R_auxi);
    padic_poly_clear(Q_auxi);
    padic_poly_clear(A_auxi);
    padic_poly_clear(B_auxi);
}   

void zqadic_reduce(zqadic_t x, zqadic_ctx_t zqadic_ctx)
{
    int prec = padic_poly_prec(x);
    zqadic_t y;
    padic_poly_t Mprec;

    zqadic_init2(y, prec, zqadic_ctx);
    padic_poly_init2(Mprec, (zqadic_ctx -> deg) + 1, prec);
    padic_poly_set(Mprec, zqadic_ctx -> M, zqadic_ctx -> pctx);

    _padic_poly_div_eucl(x, y, x, Mprec, zqadic_ctx -> pctx);
    padic_poly_reduce(x, zqadic_ctx -> pctx);

    padic_poly_clear(Mprec);
    zqadic_clear(y);
}