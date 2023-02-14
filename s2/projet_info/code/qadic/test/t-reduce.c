#include "n2adic.h"


int main()
{
    printf("-------------------- TEST DE n2adic_reduce --------------------\n");
    n2adic_ctx_t n2adic_ctx;
    
    fmpz_poly_t m;
    fmpz_poly_t a;
    fmpz_poly_t b;
    padic_poly_t M;
    int deg = 8; // Degré de l'extension
    int prec = 10; // Précision du contexte
    
    fmpz_poly_init(m);
    fmpz_poly_init(a);
    fmpz_poly_init(b);
    padic_poly_init2(M, deg + 1, prec);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    fmpz_poly_set_coeff_si(a, 0, 168);
    fmpz_poly_set_coeff_si(a, 1, 428);
    fmpz_poly_set_coeff_si(a, 2, 646);
    fmpz_poly_set_coeff_si(a, 3, 148);
    fmpz_poly_set_coeff_si(a, 4, 313);
    fmpz_poly_set_coeff_si(a, 5, 214);
    fmpz_poly_set_coeff_si(a, 6, 452);
    fmpz_poly_set_coeff_si(a, 7, 776);
    fmpz_poly_set_coeff_si(a, 8, 922);
    fmpz_poly_set_coeff_si(a, 9, 375);
    fmpz_poly_set_coeff_si(a, 10, 133);
    fmpz_poly_set_coeff_si(a, 11, 684);
    fmpz_poly_set_coeff_si(a, 12, 763);
    fmpz_poly_set_coeff_si(a, 13, 781);
    fmpz_poly_set_coeff_si(a, 14, 559);

    fmpz_poly_set_coeff_si(b, 1, -1);
    fmpz_poly_set_coeff_si(b, 256, 1);


    _n2adic_ctx_init_teichmuller(n2adic_ctx, m, prec, 0, prec, PADIC_TERSE);

    n2adic_t x;
    n2adic_t y;


    n2adic_init(x, n2adic_ctx);
    n2adic_init(y, n2adic_ctx);
    padic_poly_set_fmpz_poly(x, a, n2adic_ctx -> pctx);
    padic_poly_set_fmpz_poly(y, b, n2adic_ctx -> pctx);

    n2adic_print(x, n2adic_ctx);
    printf("\n");
    
    n2adic_reduce(x, n2adic_ctx);
    n2adic_reduce(y, n2adic_ctx);

    n2adic_print(x, n2adic_ctx);
    printf("\n");
    n2adic_print(y, n2adic_ctx);
    printf("\n");

    fmpz_poly_clear(a);
    fmpz_poly_clear(b);
    n2adic_clear(x);
    n2adic_clear(y);
    n2adic_ctx_clear(n2adic_ctx);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
}