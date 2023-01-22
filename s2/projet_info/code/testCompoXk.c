#include "stdio.h"
#include "stdlib.h"

#include "gmp.h"

#include "flint/flint.h"

#include "flint/padic.h"
#include "flint/padic_poly.h"

#include "flint/fmpz.h"
#include "flint/fmpz_poly.h"



void CompoXk(padic_poly_t P, padic_poly_t Q, fmpz_t k_conv, padic_ctx_t C) // P(X) prend la valeur Q(X^k)=(Q)o(X^k) 
{
    int N = padic_poly_prec(Q);
    int deg = padic_poly_degree(Q);
    int k =fmpz_get_si(k_conv);

    padic_t padic_temp;
    padic_poly_t padic_poly_temp;

    padic_init2(padic_temp, N);
    padic_poly_init2(padic_poly_temp, (deg + 1)*k, N);

    for (int i = 0; i < deg +1; i = i + 1)
    {
        padic_poly_get_coeff_padic(padic_temp, Q, i, C);
        padic_poly_set_coeff_padic(padic_poly_temp, i*k, padic_temp, C);
    }

    _padic_poly_set_length(P, (deg + 1)*k);
    padic_poly_set(P, padic_poly_temp, C);

    padic_poly_clear(padic_poly_temp);
    padic_clear(padic_temp);
}

void main()
{
    // Initialisation du contexte
    fmpz_t p;
    padic_ctx_t C;
    fmpz_init_set_si(p, 7);
    padic_ctx_init(C, p, 0, 20, PADIC_TERSE);

    // on construit X
    padic_poly_t X;
    padic_t un;

    // le resulta
    padic_poly_t res;
    padic_poly_init(res);

    
    padic_poly_init(X);
    padic_init2(un, 2);
    padic_one(un);

    padic_poly_set_coeff_padic(X, 1, un, C);

    CompoXk(res, X, (*C).p,C);
    padic_poly_print(res,C);
    printf("\n");

    padic_poly_clear(X);
    padic_poly_clear(res);
    padic_clear(un);


}