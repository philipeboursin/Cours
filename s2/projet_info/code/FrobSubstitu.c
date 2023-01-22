#include "stdio.h"
#include "stdlib.h"

#include "gmp.h"

#include "flint/flint.h"

#include "flint/padic.h"
#include "flint/padic_poly.h"

#include "flint/fmpz.h"
#include "flint/fmpz_poly.h"

#include "../qadic.h"


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

void frobSubstitu(qadic_t res, qadic_t x, qadic_context_t qC) // res prens la valeur \Sigma(x)
{
    CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
    reduce( res,  qC);
}

void main()
{

    qadic_ctx_t qadic_ctx;
    fmpz_t p;
    fmpz_init(p);
    fmpz_set_ui(p, 2);
    
    fmpz_poly_t m;
    padic_poly_t M;
    int n = 8; // Degré de l'extension
    int N = 10; // Précision du contexte
    
    fmpz_poly_init(m);
    padic_poly_init2(M, n + 1, N);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    _qadic_ctx_init_poly(qadic_ctx, p, m, N, 0, N, PADIC_TERSE);


    qadic_t theta;
    qadic_t res;
    padic_t un;

    qadic_init(theta, qC);    
    padic_init(un);
    padic_set_si(un, 1, (*qC).C);

    padic_poly_set_coeff_padic(theta, 1, un, (*qadic_ctx).C); // il est déja sous forme réduite
    frobSubstitu(res,theta,qC);
    qadic_print(res,qC);
    printf("\n");


    
    
}




