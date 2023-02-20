#include "zqadic.h"


int main()
{
    printf("-------------------- TEST DE zqadic_ctx_init --------------------\n");
    printf("On vérifie que zqadic_ctx_init_teichmuller calcule bien un module de Teichmuller en vérifiant qu'il divise X^q - X. Le degré de l'extension ne doit pas être trop élevé, puisque l'on fabrique X^q - X et que q est exponentiel en le degré de l'extension. \n");

    slong deg = 11;
    slong prec = 7;
    
    zqadic_ctx_t zqadic_ctx;
    fmpz_t p;
    fmpz_poly_t b;
    zqadic_t x;
    padic_poly_t M;

    fmpz_init(p);
    fmpz_set_ui(p, 2);
    fmpz_poly_init(b);
    padic_poly_init2(M, deg + 1, prec);
    zqadic_ctx_init_teichmuller(zqadic_ctx, deg, prec, 0, prec, PADIC_TERSE);
    zqadic_init(x, zqadic_ctx);
    zqadic_ctx_rep(M, zqadic_ctx);

    printf("Modulo de Teichmuller calculé : ");
    padic_poly_print(M, zqadic_ctx -> pctx);
    printf("\n");

    fmpz_poly_set_coeff_si(b, 1, -1);
    fmpz_poly_set_coeff_si(b, n_pow(2, deg), 1);
    zqadic_set_fmpz_poly(x, b, zqadic_ctx);
    zqadic_reduce(x, zqadic_ctx);

    printf("X^q - X mod M = ");
    zqadic_print(x, zqadic_ctx);
    printf("\n");
    
    fmpz_poly_clear(b);
    zqadic_clear(x);
    fmpz_clear(p);
    zqadic_ctx_clear(zqadic_ctx);
    padic_poly_clear(M);
}