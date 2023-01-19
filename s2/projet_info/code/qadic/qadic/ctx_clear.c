#include "../qadic.h"

void qadic_ctx_clear(qadic_ctx_t ctx)
{
    padic_poly_clear((*ctx).M);
    padic_ctx_clear((*ctx).C);
}