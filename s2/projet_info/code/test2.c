#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>

int main()
{
    padic_ctx_t C;
    fmpz_t p;
    fmpz_init_set_ui(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    printf("0\n");
}