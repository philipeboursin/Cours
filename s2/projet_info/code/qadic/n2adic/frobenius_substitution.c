#include "n2adic.h"


/* Calcule la substitution de Frobenius de op, \Sigma(op), et le renvoie dans rop. Supporte l'aliasing */
void n2adic_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx)
{
    if ((ctx -> type) == TEICHMULLER)
    {
        n2adic_t cache;
        n2adic_init2(cache, n2adic_prec(op), ctx);

        padic_poly_compose_pow(cache, op, 2, ctx -> pctx);
        // CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
        n2adic_reduce(cache, ctx);
        n2adic_set(rop, cache, ctx);

        n2adic_clear(cache);
    }
    else
    {
        printf("n2adic_frobenius_substitution exception : non implémenté.");
    }
}