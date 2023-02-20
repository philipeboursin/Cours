#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE zqadic_frobenius_substitution --------------------\n");
    printf("Test 1 : on vérifie que le frobenius SPARSE fonctionne bien en le calculant avec un modulo TEICHMULLER indiqué dans le contexte comme SPARSE. Le test passe si les deux calculs donnent le même résultat.\n");

    slong prec = 10;
    slong deg = 9;

    fmpz_t deux;
    flint_rand_t state;
    padic_ctx_t pctx;
    zqadic_ctx_t ctx_teich, ctx_sparse, ctx;
    zqadic_t x, y, a;
    padic_poly_t M;
    fmpz_poly_t m;

    flint_randinit(state);
    padic_poly_init2(M, deg + 1, prec);
    fmpz_poly_init(m);
    fmpz_init_set_ui(deux, 2);
    padic_ctx_init(pctx, deux, 0, prec, PADIC_TERSE);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 1, 562);
    fmpz_poly_set_coeff_si(m, 2, 1019);
    fmpz_poly_set_coeff_si(m, 3, 21);
    fmpz_poly_set_coeff_si(m, 4, 523);
    fmpz_poly_set_coeff_si(m, 5, 134);
    fmpz_poly_set_coeff_si(m, 6, 842);
    fmpz_poly_set_coeff_si(m, 7, 644);
    fmpz_poly_set_coeff_si(m, 8, 1);
    padic_poly_set_fmpz_poly(M, m, pctx);

    printf("M = ");
    padic_poly_print(M, pctx);
    printf("\n");

    zqadic_ctx_init_padic_poly(ctx_teich, M, pctx, TEICHMULLER);
    zqadic_ctx_init_padic_poly(ctx_sparse, M, pctx, SPARSE);

    zqadic_init(x, ctx_teich);
    zqadic_init(y, ctx_teich);


    for (int i = 0; i < 10; i++) zqadic_randtest(x, state, ctx_sparse);

    printf("x = ");
    zqadic_print(x, ctx_teich);
    printf("\n");

    zqadic_frobenius_substitution(y, x, ctx_sparse);
    
    printf("Sigma(x) calculé dans le contexte TEICHMULLER : ");
    zqadic_print(y, ctx_teich);
    printf("\n");

    zqadic_frobenius_substitution(y, x, ctx_teich);
    printf("Sigma(a) calculé dans le contexte SPARSE : ");
    zqadic_print(y, ctx_sparse);
    printf("\n");
    
    printf("Test 2 : on vérifie que Sigma(a)^d = a.\n");
 
    zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    // zqadic_ctx_init(ctx, deux, deg, prec, 0, prec, PADIC_TERSE);
    zqadic_init2(a, prec, ctx);

    for (int i = 0; i < 13; i++) zqadic_randtest(a, state, ctx);

    printf("x = ");
    zqadic_print(a, ctx);
    printf("\n");

    for (int i = 0; i < deg; i++)
    {
        zqadic_frobenius_substitution(a, a, ctx);
    }
 
    printf("Sigma^d(x) = ");
    zqadic_print(a, ctx);
    printf("\n");

    fmpz_clear(deux);
    flint_randclear(state);
    zqadic_ctx_clear(ctx_teich);
    zqadic_ctx_clear(ctx_sparse);
    padic_ctx_clear(pctx);
    zqadic_clear(x);
    zqadic_clear(y);
    padic_poly_clear(M);
    fmpz_poly_clear(m);
    zqadic_clear(a);
    zqadic_ctx_clear(ctx);
}