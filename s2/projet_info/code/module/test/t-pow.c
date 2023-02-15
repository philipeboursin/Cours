#include "zqadic.h"

int main()
{
    slong deg = 5;
    slong prec = 10;
    zqadic_ctx_t ctx;

    zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);

    zqadic_t x;
    fmpz_poly_t f;
    fmpz_t e;

    zqadic_init(x, ctx);
    fmpz_poly_init(f);
    fmpz_poly_set_coeff_si(f, 1, 1);
    zqadic_set_fmpz_poly(x, f, ctx);
    fmpz_init_set_ui(e, n_pow(2, deg - 1));

    zqadic_print(x, ctx);
    printf("\n");

    zqadic_pow(x, x, e, ctx);

    zqadic_print(x, ctx);
    printf("\n");
    zqadic_print((ctx -> C)[1], ctx);
    printf("\n");

    zqadic_clear(x);
    fmpz_poly_clear(f);
    fmpz_clear(e);
    zqadic_ctx_clear(ctx);
}