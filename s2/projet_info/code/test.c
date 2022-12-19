#include<stdio.h>
#include<flint/padic.h>
#include<gmp.h>

int main()
{
    fmpz_t p;
    fmpz_init_set_ui(p, 7);
    padic_ctx_t C;
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);
    
    padic_t a;
    padic_t b;
    padic_t c;
    padic_init(a);
    padic_init(b);
    padic_init(c);
    
    padic_set_ui(a, 53, C);
    padic_set_ui(b, 36, C);
    padic_add(c, a, b, C);

    padic_print(c, C);
    printf("\n");

    fmpz_clear(p);
    padic_ctx_clear(C);
}