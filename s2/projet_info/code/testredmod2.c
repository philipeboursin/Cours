
#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>





void main(  )
{
    padic_ctx_t C;
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_poly_t P;

    fmpz_t d ;
    fmpz_init_set_ui(d, padic_poly_degree(P));
    fmpz_t *coefs;

    int deg;
    deg=fmpz_get_si(d);

    for (int i = 0; i < deg+1; i++)
    {
        padic_poly_get_coeff_padic(coefs[i], P, i, C);
    }
    
    
    
}

