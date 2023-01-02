#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>




int main()
{
    padic_ctx_t C;
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    padic_poly_t P;
    padic_poly_init(P);

    padic_t a0;
    padic_init(a0);
    fmpz_t a00;
    fmpz_init_set_ui(a00, 25);
    padic_set_fmpz(a0, a00, C);

    padic_t a1; 
    padic_init(a1); 
    fmpz_t a10;
    fmpz_init_set_ui(a10, 1);
    padic_set_fmpz(a1, a10, C);

    padic_t a2;
    padic_init(a2);   
    fmpz_t a20;
    fmpz_init_set_ui(a20, 32);
    padic_set_fmpz(a2, a20, C);
    
    padic_t a3; 
    padic_init(a3);  
    fmpz_t a30;
    fmpz_init_set_ui(a30, 15);
    padic_set_fmpz(a3, a30, C);
    
    padic_t a4;
    padic_init(a4); 
    fmpz_t a40;
    fmpz_init_set_ui(a40, 3);
    padic_set_fmpz(a4, a40, C);

    

    padic_poly_set_coeff_padic(P, 0, a0, C);
    padic_poly_set_coeff_padic(P, 1, a1, C);
    padic_poly_set_coeff_padic(P, 2, a2, C);
    padic_poly_set_coeff_padic(P, 3, a3, C);
    padic_poly_set_coeff_padic(P, 4, a4, C);

    padic_poly_t res;
    padic_poly_init(res);

    padic_poly_t X2;
    padic_poly_init(X2);
    padic_t a;
    padic_init(a);
    padic_one(a);
    padic_poly_set_coeff_padic(X2,2,a, C);
    padic_poly_compose(res, P, X2, C);

    padic_poly_print(P,C);
    printf("\n");
    padic_poly_print(res,C);

}