#include "n2adic.h"

void frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx) // res prens la valeur \Sigma(x)
{
    n2adic_t cache;
    n2adic_init(cache, ctx);

    padic_poly_compose_pow(cache, op, 2, ctx->ctx);
    // CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
    n2adic_reduce(cache, ctx);
    n2adic_set(rop, cache, ctx);

    n2adic_clear(cache);
}