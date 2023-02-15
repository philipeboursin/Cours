#include "zqadic.h"


int main()
{
    zqadic_ctx_t zqadic_ctx;
    fmpz_t p;
    fmpz_poly_t b;

    fmpz_init(p);
    fmpz_set_ui(p, 2);
    fmpz_poly_init(b);
    
    
    // fmpz_poly_t m;
    padic_poly_t M;
    int deg = 8; // Degré de l'extension
    int prec = 10; // Précision du contexte
    
    // fmpz_poly_init(m);
    padic_poly_init2(M, deg + 1, prec);

    fmpz_poly_set_coeff_si(b, 1, -1);
    fmpz_poly_set_coeff_si(b, n_pow(2, deg), 1);

    zqadic_ctx_init_teichmuller(zqadic_ctx, deg, prec, 0, prec, PADIC_TERSE);

    zqadic_ctx_rep(M, zqadic_ctx);
    padic_poly_print(M, zqadic_ctx -> pctx);
    printf("\n");

    zqadic_print((zqadic_ctx -> C)[0], zqadic_ctx);
    printf("\n");
    zqadic_print((zqadic_ctx -> C)[1], zqadic_ctx);
    printf("\n");

    zqadic_t x;
    zqadic_init(x, zqadic_ctx);
    zqadic_set_fmpz_poly(x, b, zqadic_ctx);

    zqadic_reduce(x, zqadic_ctx);
    zqadic_print(x, zqadic_ctx);
    printf("\n");
    
    fmpz_poly_clear(b);
    zqadic_clear(x);
    fmpz_clear(p);
    zqadic_ctx_clear(zqadic_ctx);
    padic_poly_clear(M);
}