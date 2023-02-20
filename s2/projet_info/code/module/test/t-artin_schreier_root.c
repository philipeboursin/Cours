#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE zqadic_artin_schreier_root --------------------\n");
    int deg = 10;
    int prec = 20;
    zqadic_ctx_t ctx;
    zqadic_t x;
    zqadic_t alpha;
    zqadic_t beta;
    zqadic_t gamma;
    zqadic_t cache1;
    zqadic_t cache2;
    flint_rand_t state;

    flint_randinit(state);

    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    // zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    zqadic_ctx_init(ctx, p, deg, prec, 0, prec, PADIC_TERSE);
    
    zqadic_init(x, ctx);
    zqadic_init(alpha, ctx);
    zqadic_init(beta, ctx);
    zqadic_init(gamma, ctx);
    zqadic_init(cache1, ctx);
    zqadic_init(cache2, ctx);

    int b = 1;
    int i = 0;

    while (i < 1000)
    {
        zqadic_randtest(alpha, state, ctx);
        zqadic_randtest(beta, state, ctx);
        zqadic_randtest(gamma, state, ctx);

        if (zqadic_val(beta) > 0 && zqadic_val(alpha) == 0 && zqadic_val(gamma) >= 0)
        {
            i++;
            zqadic_artin_schreier_root(x, alpha, beta, gamma, ctx);
            zqadic_frobenius_substitution(cache1, x, ctx);
            zqadic_mul(cache1, alpha, cache1, ctx);
            zqadic_mul(cache2, beta, x, ctx);
            zqadic_add(cache1, cache2, cache1, ctx);
            zqadic_add(cache1, gamma, cache1, ctx);
            if (padic_poly_is_zero(cache1) == 0)
            {
                b = 0;
                printf("alpha = ");
                zqadic_print(alpha, ctx);
                printf("\n");
                printf("beta = ");
                zqadic_print(beta, ctx);
                printf("\n");
                printf("gamma = ");
                zqadic_print(gamma, ctx);
                printf("\n");
                printf("x = ");
                zqadic_print(x, ctx);
                printf("\n");
                zqadic_frobenius_substitution(x, x, ctx);
                printf("Sigma x = ");
                zqadic_print(x, ctx);
                printf("\n");
            }
        }
    }
    printf("Test sur plusieurs instances : on résout l'équation 10000 fois avec des paramètres aléatoires, et on vérifie que l'algorithme renvoie le bon résultat en vérifiant qu'il satisfait l'équation. Si le test est passé, affiche 1, sinon 0.\n");
    printf("%d\n", b);

    zqadic_ctx_clear(ctx);
    zqadic_clear(x);
    zqadic_clear(alpha);
    zqadic_clear(beta);
    zqadic_clear(gamma);
    zqadic_clear(cache1);
    zqadic_clear(cache2);
    flint_randclear(state);
}