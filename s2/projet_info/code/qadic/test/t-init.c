#include "n2adic.h"

int main()
{
    n2adic_ctx_t n2adic_ctx;    
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

    _n2adic_ctx_init_poly(n2adic_ctx, m, prec, 0, prec, PADIC_TERSE);

    n2adic_t x;
    n2adic_init(x, n2adic_ctx); 

    n2adic_clear(x);
    n2adic_ctx_clear(n2adic_ctx);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
}