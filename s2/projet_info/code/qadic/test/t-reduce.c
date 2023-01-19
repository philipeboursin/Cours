#include "../qadic.h"

int main()
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

    qadic_t x;
    padic_t un;

    qadic_init(x, qadic_ctx);    
    padic_init(un);
    padic_set_si(un, 1, (*qadic_ctx).C);

    padic_poly_set_coeff_padic(x, 1, un, (*qadic_ctx).C);
    qadic_print(x, qadic_ctx);
    printf("\n");
    
    qadic_reduce(x, qadic_ctx);

    qadic_print(x, qadic_ctx);
    printf("\n");

    padic_clear(un);
    qadic_clear(x);
    fmpz_clear(p);
    qadic_ctx_clear(qadic_ctx);
    fmpz_poly_clear(m);
    padic_poly_clear(M);

}