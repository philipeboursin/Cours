#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE padic_poly_symetric --------------------\n");

    slong prec = 10;
    slong deg = 10;

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
    padic_poly_symetric(P, P, ctx);
    printf("Symétrique de P = ");
    padic_poly_print(P, ctx);
    printf("\n");

    fmpz_clear(p);
    padic_poly_clear(P);
    padic_ctx_clear(ctx);
    flint_randclear(state);
}