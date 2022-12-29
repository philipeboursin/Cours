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
    padic_zero(x);
    
    fmpz_t xx;
    fmpz_init_set_ui(xx, 16);
    padic_set_fmpz(x, xx, C);
    //padic_print(x, C);
    
    fmpz_t v;
    fmpz_init_set_ui(v, padic_val(x));
    fmpz_print(v);
}