#include "n2adic.h"

int main()
{
    printf("-------------------- TEST DE n2adic_inv --------------------\n");
    n2adic_ctx_t n2adic_ctx;    
    fmpz_poly_t m;
    padic_poly_t M;
    fmpz_poly_t a;
    padic_poly_t A;
    flint_rand_t state;
    n2adic_t x;
    n2adic_t inv_x;

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

    _n2adic_ctx_init_teichmuller(n2adic_ctx, m, prec, 0, prec, PADIC_TERSE);

    padic_poly_set_fmpz_poly(A, a, n2adic_ctx -> pctx);

    n2adic_init(x, n2adic_ctx);
    n2adic_init(inv_x, n2adic_ctx); 
    n2adic_set_padic_poly(x, A, n2adic_ctx);


    n2adic_inv(inv_x, x, n2adic_ctx);

    printf("Test du handbook, page 247 :\n");
    printf("a = ");
    n2adic_print(x, n2adic_ctx);
    printf("\n");
    printf("a^{-1} = ");
    n2adic_print(inv_x, n2adic_ctx);
    printf("\n");

    int b = 1;
    for (int i = 0; i < 1000; i++)
    {
        n2adic_randtest(x, state, n2adic_ctx);
        long val = padic_poly_val(x);
        if (val == 0)
        {
            // printf("%ld\n", val);
            n2adic_inv(inv_x, x, n2adic_ctx);
            n2adic_mul(x, x, inv_x, n2adic_ctx);
            if (n2adic_is_one(x) != 1) b = 0;
        }
    }

    printf("Test sur plusieurs instances : on inverse des éléments aléatoires de Zq (inversibles) et on vérifie que le produit d'eux-même avec leur inverse vaut 1. Si le test est passé, affiche 1, sinon 0.\n");
    printf("%d\n", b);

    n2adic_clear(x);
    n2adic_clear(inv_x);
    flint_randclear(state);
    padic_poly_clear(A);
    fmpz_poly_clear(a);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
    n2adic_ctx_clear(n2adic_ctx);
}