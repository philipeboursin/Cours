#include "n2adic.h"

void n2adic_pow(n2adic_t rop, n2adic_t op, fmpz_t e, n2adic_ctx_t ctx)
{
    slong prec = n2adic_prec(rop);

    n2adic_t temp;
    n2adic_t pow;
    fmpz_t q;
    fmpz_t r;

    n2adic_init2(temp, prec, ctx);
    n2adic_init2(pow, prec, ctx);
    n2adic_one(temp);
    n2adic_set(pow, op, ctx);
    fmpz_init_set(q, e);
    fmpz_init(r);

    while (fmpz_is_zero(q) != 1)
    {
        fmpz_mod_ui(r, q, 2);
        fmpz_fdiv_q_si(q, q, 2);
        if (fmpz_is_one(r) == 1)
        {
            n2adic_mul(temp, temp, pow, ctx);
        }
        n2adic_mul(pow, pow, pow, ctx);
    }
    n2adic_set(rop, temp, ctx);

    n2adic_clear(temp);
    n2adic_clear(pow);
    fmpz_clear(q);
    fmpz_clear(r);
}