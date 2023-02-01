#include "n2adic.h"

int main()
{
    printf("-------------------- TEST DE n2adic_artin_schreier_root --------------------\n");
    int deg = 6;
    int prec = 10;
    n2adic_ctx_t ctx;
    n2adic_t x;
    n2adic_t alpha;
    n2adic_t beta;
    n2adic_t gamma;
    n2adic_t cache1;
    n2adic_t cache2;
    flint_rand_t state;

    flint_randinit(state);

    n2adic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);
    
    n2adic_init(x, ctx);
    n2adic_init(alpha, ctx);
    n2adic_init(beta, ctx);
    n2adic_init(gamma, ctx);
    n2adic_init(cache1, ctx);
    n2adic_init(cache2, ctx);

    int b = 1;

    for (int i = 0; i < 10000; i++)
    {
        n2adic_randtest(alpha, state, ctx);
        n2adic_randtest(beta, state, ctx);
        n2adic_randtest(gamma, state, ctx);

        if (n2adic_val(beta) > 0 && n2adic_val(alpha) == 0 && n2adic_val(gamma) >= 0)
        {
            n2adic_artin_schreier_root(x, alpha, beta, gamma, ctx);
            n2adic_frobenius_substitution(cache1, x, ctx);
            n2adic_mul(cache1, alpha, cache1, ctx);
            n2adic_mul(cache2, beta, x, ctx);
            n2adic_add(cache1, cache2, cache1, ctx);
            n2adic_add(cache1, gamma, cache1, ctx);

            if (padic_poly_is_zero(cache1) == 0)
            {
                b = 0;
            }
        }
    }
    printf("Test sur plusieurs instances : on résout l'équation 10000 fois avec des paramètres aléatoires, et on vérifie que l'algorithme renvoie le bon résultat en vérifiant qu'il satisfait l'équation. Si le test est passé, affiche 1, sinon 0.\n");
    printf("%d\n", b);

    n2adic_ctx_clear(ctx);
    n2adic_clear(x);
    n2adic_clear(alpha);
    n2adic_clear(beta);
    n2adic_clear(gamma);
    n2adic_clear(cache1);
    n2adic_clear(cache2);
    flint_randclear(state);
}