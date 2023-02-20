#include "zqadic.h"

int main()
{
    int prec = 10;
    int deg = 10;

    fmpz_t p;
    padic_ctx_t ctx;
    padic_poly_t P;
    flint_rand_t state;

    fmpz_init_set_ui(p, 2);
    padic_ctx_init(ctx, p, 0, prec, PADIC_TERSE);
    padic_poly_init2(P, deg + 1, prec);
    flint_randinit(state);

    for (int i = 0; i < 15; i++) padic_poly_randtest(P, state, deg + 1, ctx);

    printf("P = ");
    padic_poly_print(P, ctx);
    printf("\n");
    _coeff_symetry(P, P, ctx);
    printf("P renversé = ");
    padic_poly_print(P, ctx);
    printf("\n");
}