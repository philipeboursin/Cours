#include "zqadic.h"

int main()
{
    zqadic_ctx_t ctx;    
    fmpz_poly_t m;
    padic_poly_t M;

    int deg = 8; // Degré de l'extension
    int prec = 10; // Précision du contexte
    
    fmpz_poly_init(m);
    padic_poly_init2(M, deg + 1, prec);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    _zqadic_ctx_init_teichmuller(ctx, m, prec, 0, prec, PADIC_TERSE);

    zqadic_t x;
    zqadic_init(x, ctx); 

    zqadic_clear(x);
    zqadic_ctx_clear(ctx);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
}