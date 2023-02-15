#include "zqadic.h"


/* Calcule la substitution de Frobenius de op, \Sigma(op), et le renvoie dans rop. Supporte l'aliasing */
void zqadic_frobenius_substitution(zqadic_t rop, zqadic_t op, zqadic_ctx_t ctx)
{
    if ((ctx -> type) == TEICHMULLER)
    {
        zqadic_t cache;
        zqadic_init2(cache, zqadic_prec(op), ctx);

        padic_poly_compose_pow(cache, op, 2, ctx -> pctx);
        // CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
        zqadic_reduce(cache, ctx);
        zqadic_set(rop, cache, ctx);

        zqadic_clear(cache);
    }
    else
    {
        // zqadic_composition(rop, op, )
        printf("zqadic_frobenius_substitution exception : non implémenté.");
        exit(-1);
    }
}