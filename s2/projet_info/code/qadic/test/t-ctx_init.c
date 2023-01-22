#include "../qadic.h"


void main()
{
    qadic_ctx_t qadic_ctx;
    fmpz_t p;
    fmpz_poly_t b;

    fmpz_init(p);
    fmpz_set_ui(p, 2);
    fmpz_poly_init(b);
    
    
    // fmpz_poly_t m;
    padic_poly_t M;
    int n = 8; // Degré de l'extension
    int N = 10; // Précision du contexte
    
    // fmpz_poly_init(m);
    padic_poly_init2(M, n + 1, N);

    fmpz_poly_set_coeff_si(b, 1, -1);
    fmpz_poly_set_coeff_si(b, n_pow(2, n), 1);

    qadic_ctx_init(qadic_ctx, p, n, N, 0, N, PADIC_TERSE);

    qadic_ctx_rep(M, qadic_ctx);
    padic_poly_print(M, (*qadic_ctx).C);
    printf("\n");

    qadic_t x;
    qadic_init(x, qadic_ctx);
    padic_poly_set_fmpz_poly(x, b, (*qadic_ctx).C);

    qadic_reduce(x, qadic_ctx);
    qadic_print(x, qadic_ctx);
    printf("\n");
    
    fmpz_poly_clear(b);
    qadic_clear(x);
    fmpz_clear(p);
    qadic_ctx_clear(qadic_ctx);
    padic_poly_clear(M);
}