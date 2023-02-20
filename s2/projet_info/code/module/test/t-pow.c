#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE zqadic_pow --------------------\n");
    printf("On vérifie que X^{p^d} = X : \n");

    slong deg = 7;
    slong prec = 10;
    fmpz_t p;
    zqadic_ctx_t ctx;
    zqadic_t x, y;
    fmpz_poly_t P;
    fmpz_t e, f;

    fmpz_init_set_ui(p, 2);
    zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    // zqadic_ctx_init(ctx, p, deg, prec, 0, prec, PADIC_TERSE);


    zqadic_init(x, ctx);
    zqadic_init(y, ctx);
    fmpz_poly_init(P);
    fmpz_poly_set_coeff_si(P, 1, 1);
    zqadic_set_fmpz_poly(x, P, ctx);
    fmpz_init_set_ui(e, n_pow(2, deg - 1));
    fmpz_init_set_ui(f, n_pow(2, deg));

    printf("X : ");
    zqadic_print(x, ctx);
    printf("\n");

    zqadic_pow(y, x, e, ctx);
    zqadic_pow(x, x, f, ctx);
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
    zqadic_clear(y);
    fmpz_poly_clear(P);
    fmpz_clear(e);
    fmpz_clear(f);
    zqadic_ctx_clear(ctx);
}