#include "zqadic.h"

void zqadic_ctx_change_prec(zqadic_ctx_t ctx, slong prec)
{
    if ((ctx -> type) == SPARSE) (ctx -> prec) = prec;
    else
    {
        padic_poly_t m;
        padic_poly_t M;
        
        padic_poly_init2(m, padic_poly_degree(ctx -> M) + 1, 1);
        padic_poly_init2(M, padic_poly_degree(ctx -> M) + 1, prec);
        padic_poly_set(m, ctx -> M, ctx -> pctx);
        _teichmuller_modulus(M, m, prec, ctx -> pctx);
        padic_poly_set(ctx -> M, M, ctx -> pctx);
        (ctx -> prec) = prec;

        padic_poly_clear(m);
        padic_poly_clear(M);
    }
}