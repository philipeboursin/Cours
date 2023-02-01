#include "n2adic.h"

int main()
{
    slong deg = 5;
    slong prec = 10;
    n2adic_ctx_t ctx;

    n2adic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);

    n2adic_t x;
    fmpz_poly_t f;
    fmpz_t e;

    n2adic_init(x, ctx);
    fmpz_poly_init(f);
    fmpz_poly_set_coeff_si(f, 1, 1);
    n2adic_set_fmpz_poly(x, f, ctx);
    fmpz_init_set_ui(e, n_pow(2, deg - 1));

    n2adic_print(x, ctx);
    printf("\n");

    n2adic_pow(x, x, e, ctx);

    n2adic_print(x, ctx);
    printf("\n");
    n2adic_print((ctx -> C)[1], ctx);
    printf("\n");

    n2adic_clear(x);
    fmpz_poly_clear(f);
    fmpz_clear(e);
    n2adic_ctx_clear(ctx);
}