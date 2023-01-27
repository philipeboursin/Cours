#include "n2adic.h"

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

void _coeff_symetry(padic_poly_t P, padic_poly_t Q, padic_ctx_t C) // Procédure qui transforme P en un polynôme dont les coefficients sont ceux de Q renversés
{
    int deg = padic_poly_degree(Q);
    int N = padic_poly_prec(Q);

    padic_poly_t R;
    padic_t padic_cache;
    padic_poly_init2(R, deg, N);
    padic_init2(padic_cache, N);

    for (int i = 0; i < deg + 1; i++)
    {
        padic_poly_get_coeff_padic(padic_cache, Q, i, C);
        padic_poly_set_coeff_padic(R, deg-i, padic_cache, C);
    }

    padic_poly_set(P, R, C);

    padic_poly_clear(R);
    padic_clear(padic_cache);
}

// Ne fonctionne que si B est unitaire
void _padic_poly_div_eucl_auxi(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C)
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
        // padic_poly_inv_series(P2, P2, n, C);
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

// Fonctionne même avec B non unitaire, le divise par son coefficient directeur et utilise _padic_poly_div_eucl_auxi
void _padic_poly_div_eucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t ctx)
{
    padic_t c;
    padic_t d;
    padic_poly_t B_monic;

    int prec = padic_poly_prec(B);
    int degB = padic_poly_degree(B);

    padic_init2(c, prec);
    padic_init2(d, prec);
    padic_poly_init2(B_monic, degB, prec);

    padic_poly_get_coeff_padic(c, B, degB, ctx);
    padic_inv(d, c, ctx); // d est l'inverse de c
    padic_poly_scalar_mul_padic(B_monic, B, d, ctx);

    _padic_poly_div_eucl_auxi(A, B_monic, R, Q, ctx);

    padic_poly_scalar_mul_padic(Q, Q, c, ctx);

    padic_clear(c);
    padic_clear(d);
    padic_poly_clear(B_monic);
}

void n2adic_reduce(n2adic_t x, n2adic_ctx_t n2adic_ctx)
{
    int prec = padic_poly_prec(x);
    n2adic_t y;
    padic_poly_t Mprec;

    n2adic_init2(y, prec, n2adic_ctx);
    padic_poly_init2(Mprec, (n2adic_ctx -> deg) + 1, prec);
    padic_poly_set(Mprec, n2adic_ctx -> M, n2adic_ctx -> ctx);

    _padic_poly_div_eucl(x, Mprec, x, y, n2adic_ctx -> ctx);
    padic_poly_reduce(x, n2adic_ctx -> ctx);

    n2adic_clear(y);
}