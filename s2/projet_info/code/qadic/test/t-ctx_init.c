#include "../qadic.h"


void main()
{
    qadic_ctx_t qadic_ctx;
    fmpz_t p;
    fmpz_init(p);
    fmpz_set_ui(p, 2);
    
    fmpz_poly_t m;
    padic_poly_t M;
    int n = 8; // Degré de l'extension
    int N = 10; // Précision du contexte
    
    fmpz_poly_init(m);
    padic_poly_init2(M, n + 1, N);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    _qadic_ctx_init_poly(qadic_ctx, p, m, N, 0, N, PADIC_TERSE);

    qadic_ctx_rep(M, qadic_ctx);
    padic_poly_print(M, (*qadic_ctx).C);
    printf("\n");

    fmpz_clear(p);
    qadic_ctx_clear(qadic_ctx);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
}