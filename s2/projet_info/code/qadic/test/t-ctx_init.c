#include "n2adic.h"


int main()
{
    n2adic_ctx_t n2adic_ctx;
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

    n2adic_ctx_init(n2adic_ctx, deg, prec, 0, prec, PADIC_TERSE);

    n2adic_ctx_rep(M, n2adic_ctx);
    padic_poly_print(M, n2adic_ctx -> ctx);
    printf("\n");

    n2adic_t x;
    n2adic_init(x, n2adic_ctx);
    n2adic_set_fmpz_poly(x, b, n2adic_ctx);

    n2adic_reduce(x, n2adic_ctx);
    n2adic_print(x, n2adic_ctx);
    printf("\n");
    
    fmpz_poly_clear(b);
    n2adic_clear(x);
    fmpz_clear(p);
    n2adic_ctx_clear(n2adic_ctx);
    padic_poly_clear(M);
}