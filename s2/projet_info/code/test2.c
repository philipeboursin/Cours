#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>








void main()
{
    padic_ctx_t C;
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_poly_t d;    
    padic_poly_init(d);

    padic_t x;
    padic_init2(x,4);
    padic_zero(x);
    
    fmpz_t xx;
    fmpz_init_set_ui(xx, 25);
    padic_set_fmpz(x, xx, C);
    //padic_init2(x,3);
    padic_print(x, C);
    //int N;
    //N=padic_get_prec(x);
    //printf( "la precision est %d /n", N);
}




 void truc()
{
    
    padic_ctx_t C;
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_poly_t P;
    padic_poly_one(P);

    
    padic_t coefs[32];
    padic_t a;
    fmpz_t aa;
    fmpz_init_set_ui(aa, 16);
    padic_set_fmpz(a, aa, C);


    for (int i = 0; i < 5; i++)
    {
        padic_poly_set_coeff_padic(P,i,a,C);
    }
    
    fmpz_t d ;
    fmpz_init_set_ui(d, padic_poly_degree(P));
    int deg;
    deg=fmpz_get_si(d);

    

    //padic_init2(padic_t rop, slong N)

   // for (int i = 0; i < deg; i++)
   //{
   //     padic_poly_get_coeff_padic(coefs[i], P, i, C);
   // }

    
}