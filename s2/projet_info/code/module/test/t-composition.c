#include "zqadic.h"

int main()
{
    fmpz_t p;
    zqadic_ctx_t ctx;
    padic_t one;
    padic_poly_t P;
    zqadic_t x;

    int deg = 5;
    int prec = 10;

    fmpz_init_set_ui(p, 2);
    zqadic_ctx_init(ctx, p, deg, prec, 0, prec, PADIC_TERSE);

    zqadic_init(x, ctx);
    padic_poly_init2(P, 0, prec);
    padic_init2(one, prec);
    padic_set_ui(one, 2, ctx -> pctx);

    padic_poly_set_coeff_padic(P, 2, one, ctx -> pctx);
    zqadic_set_padic_poly(x, P, ctx);

    printf("x = ");
    zqadic_print(x, ctx);
    printf("\n");

    zqadic_composition(x, x, x, ctx);
    
    printf("x = ");
    zqadic_print(x, ctx);
    printf("\n");
}