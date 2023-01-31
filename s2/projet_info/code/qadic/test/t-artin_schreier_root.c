#include "n2adic.h"

int main()
{
    int deg = 5;
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

    n2adic_ctx_init(ctx, deg, prec, 0, prec, PADIC_TERSE);
    
    n2adic_init(x, ctx);
    n2adic_init(alpha, ctx);
    n2adic_init(beta, ctx);
    n2adic_init(gamma, ctx);
    n2adic_init(cache1, ctx);
    n2adic_init(cache2, ctx);

    for (int i = 0; i < 100; i++)
    {
        n2adic_randtest(alpha, state, ctx);
        n2adic_randtest(beta, state, ctx);
        n2adic_randtest(gamma, state, ctx);

        if (n2adic_val(beta) > 0 && n2adic_val(alpha) == 0)
        {
            n2adic_artin_schreier_root(x, alpha, beta, gamma, ctx);
            n2adic_frobenius_substitution(cache1, x, ctx);
            n2adic_mul(cache1, alpha, cache1, ctx);
            n2adic_mul(cache2, beta, x, ctx);
            n2adic_add(cache1, cache2, cache1, ctx);
            n2adic_add(cache1, gamma, cache1, ctx);
            
            printf("aled = ");
            n2adic_print(cache1, ctx);
            printf("\n");
        }
    }
}