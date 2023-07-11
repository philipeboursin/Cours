#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE zqadic_inv_frobenius_substitution --------------------\n");

    slong deg = 100;
    slong prec = 100;

    flint_rand_t state;
    flint_randinit(state);

    zqadic_ctx_t ctx;
    zqadic_t x;
    zqadic_t y;

    zqadic_ctx_init_teichmuller(ctx, deg, prec, 0, prec, PADIC_TERSE);

    zqadic_init(x, ctx);
    zqadic_init(y, ctx);

    int b = 1;
    int N = 1000;
    printf("Test sur plusieurs instances : on calcule des inverses pour %d éléments de Zq aléatoires, et on vérifie qu'en appliquant Sigma on retombe bien sur l'élément de départ. Si le test est passé, affiche 1, sinon 0.\n", N);

    for(int i = 0; i < N; i++)
    {
        zqadic_randtest(x, state, ctx);
        zqadic_inv_frobenius_substitution(y, x, ctx);
        zqadic_frobenius_substitution(y, y, ctx);
        if(zqadic_equal(x, y) != 1) b = 0;
    }
    printf("%d\n", b);

    flint_randclear(state);
    zqadic_clear(x);
    zqadic_clear(y);
    zqadic_ctx_clear(ctx);
}