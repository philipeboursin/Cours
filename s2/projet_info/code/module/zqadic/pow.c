#include "zqadic.h"

void zqadic_pow(zqadic_t rop, zqadic_t op, fmpz_t e, zqadic_ctx_t ctx)
{
    slong prec = zqadic_prec(rop);

    zqadic_t temp;
    zqadic_t pow;
    fmpz_t q;
    fmpz_t r;

    zqadic_init2(temp, prec, ctx);
    zqadic_init2(pow, prec, ctx);
    zqadic_one(temp);
    zqadic_set(pow, op, ctx);
    fmpz_init_set(q, e);
    fmpz_init(r);

    while (fmpz_is_zero(q) != 1)
    {
        fmpz_mod_ui(r, q, 2);
        fmpz_fdiv_q_si(q, q, 2);
        if (fmpz_is_one(r) == 1)
        {
            zqadic_mul(temp, temp, pow, ctx);
        }
        zqadic_mul(pow, pow, pow, ctx);
    }
    zqadic_set(rop, temp, ctx);

    zqadic_clear(temp);
    zqadic_clear(pow);
    fmpz_clear(q);
    fmpz_clear(r);
}