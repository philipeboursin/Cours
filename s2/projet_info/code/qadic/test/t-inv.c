#include "n2adic.h"

int main()
{
    n2adic_ctx_t n2adic_ctx;    
    fmpz_poly_t m;
    padic_poly_t M;
    fmpz_poly_t a;
    padic_poly_t A;

    flint_rand_t state;
    flint_randinit(state);

    int deg = 8; // Degré de l'extension
    int prec = 10; // Précision du contexte
    
    fmpz_poly_init(m);
    fmpz_poly_init(a);
    padic_poly_init2(M, deg + 1, prec);
    padic_poly_init2(A, deg, prec);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    fmpz_poly_set_coeff_si(a, 0, 591);
    fmpz_poly_set_coeff_si(a, 1, 650);
    fmpz_poly_set_coeff_si(a, 2, 423);
    fmpz_poly_set_coeff_si(a, 3, 918);
    fmpz_poly_set_coeff_si(a, 4, 458);
    fmpz_poly_set_coeff_si(a, 5, 724);
    fmpz_poly_set_coeff_si(a, 6, 303);
    fmpz_poly_set_coeff_si(a, 7, 982);

    padic_poly_set_fmpz_poly(A, a, n2adic_ctx -> ctx);

    _n2adic_ctx_init_poly(n2adic_ctx, m, prec, 0, prec, PADIC_TERSE);

    n2adic_t x;
    n2adic_t inv_x;
    n2adic_init(x, n2adic_ctx);
    n2adic_init(inv_x, n2adic_ctx); 
    n2adic_set_padic_poly(x, A, n2adic_ctx);


    n2adic_inv(inv_x, x, n2adic_ctx);

    printf("x = ");
    n2adic_print(x, n2adic_ctx);
    printf("\n");
    printf("x^{-1} = ");
    n2adic_print(inv_x, n2adic_ctx);
    printf("\n");
    n2adic_mul(x, x, inv_x, n2adic_ctx);
    printf("xx^{-1} = ");
    n2adic_print(x, n2adic_ctx);
    printf("\n");

    for (int i = 0; i < 100; i++)
    {
        n2adic_randtest(x, state, n2adic_ctx);
        long val = padic_poly_val(x);
        // printf("%ld\n", val);
        if (val == 0)
        {
            n2adic_inv(inv_x, x, n2adic_ctx);
            n2adic_mul(x, x, inv_x, n2adic_ctx);
            printf("xx^{-1} = ");
            n2adic_print(x, n2adic_ctx);
            printf("\n");
        }
    }

    n2adic_clear(x);
    n2adic_ctx_clear(n2adic_ctx);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
}