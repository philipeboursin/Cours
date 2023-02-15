#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE zqadic_inv --------------------\n");
    zqadic_ctx_t zqadic_ctx;    
    fmpz_poly_t m;
    padic_poly_t M;
    fmpz_poly_t a;
    padic_poly_t A;
    flint_rand_t state;
    zqadic_t x;
    zqadic_t inv_x;

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

    _zqadic_ctx_init_teichmuller(zqadic_ctx, m, prec, 0, prec, PADIC_TERSE);

    padic_poly_set_fmpz_poly(A, a, zqadic_ctx -> pctx);

    zqadic_init(x, zqadic_ctx);
    zqadic_init(inv_x, zqadic_ctx); 
    zqadic_set_padic_poly(x, A, zqadic_ctx);


    zqadic_inv(inv_x, x, zqadic_ctx);

    printf("Test du handbook, page 247 :\n");
    printf("a = ");
    zqadic_print(x, zqadic_ctx);
    printf("\n");
    printf("a^{-1} = ");
    zqadic_print(inv_x, zqadic_ctx);
    printf("\n");

    int b = 1;
    for (int i = 0; i < 1000; i++)
    {
        zqadic_randtest(x, state, zqadic_ctx);
        long val = padic_poly_val(x);
        if (val == 0)
        {
            // printf("%ld\n", val);
            zqadic_inv(inv_x, x, zqadic_ctx);
            zqadic_mul(x, x, inv_x, zqadic_ctx);
            if (zqadic_is_one(x) != 1) b = 0;
        }
    }

    printf("Test sur plusieurs instances : on inverse des éléments aléatoires de Zq (inversibles) et on vérifie que le produit d'eux-même avec leur inverse vaut 1. Si le test est passé, affiche 1, sinon 0.\n");
    printf("%d\n", b);

    zqadic_clear(x);
    zqadic_clear(inv_x);
    flint_randclear(state);
    padic_poly_clear(A);
    fmpz_poly_clear(a);
    fmpz_poly_clear(m);
    padic_poly_clear(M);
    zqadic_ctx_clear(zqadic_ctx);
}