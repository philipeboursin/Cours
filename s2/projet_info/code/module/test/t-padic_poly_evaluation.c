#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE padic_poly_evaluation --------------------\n");

    fmpz_t p;
    zqadic_ctx_t ctx;
    padic_poly_t P;
    padic_t a, one;
    zqadic_t x, xp;

    slong deg = 11;
    slong prec = 12;

    fmpz_init_set_ui(p, 2);
    zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    zqadic_init(x, ctx);
    padic_poly_init2(P, 0, prec);
    padic_init2(a, prec);
    zqadic_init2(xp, 1, ctx);
    padic_init2(one, 1);

    padic_set_ui(a, 2, ctx -> pctx);
    padic_poly_set_coeff_padic(P, 2, a, ctx -> pctx);
    zqadic_set_padic_poly(x, P, ctx);

    printf("Test 1 : on évalue 2X^2 avec lui même.\n");

    zqadic_padic_poly_evaluation(x, x, x, ctx);
    
    printf("2(2X^2)^2 = ");
    zqadic_print(x, ctx);
    printf("\n");

    printf("Test 2 : on évalue M modulo d'un contexte teichmuller avec X^p.\n");

    padic_one(one);
    padic_poly_set_coeff_padic(xp, fmpz_get_ui(p), one, ctx -> pctx);

    printf("M = ");
    padic_poly_print(ctx -> M, ctx -> pctx);
    printf("\n");

    zqadic_padic_poly_evaluation(x, ctx -> M, xp, ctx);

    printf("M(X^p) = ");
    zqadic_print(x, ctx);
    printf("\n");

    fmpz_clear(p);
    padic_clear(a);
    padic_poly_clear(P);
    zqadic_clear(x);
    zqadic_clear(xp);
    padic_clear(one);
    zqadic_ctx_clear(ctx);
}