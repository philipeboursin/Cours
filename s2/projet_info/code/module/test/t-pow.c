#include "zqadic.h"

int main()
{
    slong deg = 7;
    slong prec = 10;
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    zqadic_ctx_t ctx;

    zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    // zqadic_ctx_init(ctx, p, deg, prec, 0, prec, PADIC_TERSE);

    zqadic_t x, y;
    fmpz_poly_t f;
    fmpz_t e, g;

    zqadic_init(x, ctx);
    zqadic_init(y, ctx);
    fmpz_poly_init(f);
    fmpz_poly_set_coeff_si(f, 1, 1);
    zqadic_set_fmpz_poly(x, f, ctx);
    fmpz_init_set_ui(e, n_pow(2, deg - 1));
    fmpz_init_set_ui(g, n_pow(2, deg));

    printf("X : ");
    zqadic_print(x, ctx);
    printf("\n");

    zqadic_pow(y, x, e, ctx);
    zqadic_pow(x, x, g, ctx);
    printf("X^{p^d} = ");
    zqadic_print(x, ctx);
    printf("\n");
    printf("X^{p^{d - 1}} = ");
    zqadic_print(y, ctx);
    printf("\n");
    printf("C_1 = ");
    zqadic_print((ctx -> C)[1], ctx);
    printf("\n");

    zqadic_clear(x);
    fmpz_poly_clear(f);
    fmpz_clear(e);
    zqadic_ctx_clear(ctx);
}