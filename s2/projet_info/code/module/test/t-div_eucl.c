#include "zqadic.h"

int main()
{
    fmpz_t deux;
    padic_ctx_t ctx;
    padic_poly_t A;
    padic_poly_t B;
    padic_poly_t Q;
    padic_poly_t R;
    padic_poly_t cache;
    flint_rand_t state;
    padic_t one;

    int prec = 10;

    padic_init2(one, prec);
    fmpz_init_set_ui(deux, 2);  
    padic_ctx_init(ctx, deux, 0, prec, PADIC_TERSE);
    padic_poly_init2(A, 9, prec);
    padic_poly_init2(B, 5, prec);
    padic_poly_init2(Q, 0, prec);
    padic_poly_init2(R, 0, prec);
    padic_poly_init2(cache, 0, prec);
    flint_randinit(state);
    padic_one(one);

    for (int i = 0; i < 3; i++)
    {
        padic_poly_randtest(A, state, 9, ctx);
        padic_poly_randtest(B, state, 6, ctx);
        padic_poly_set_coeff_padic(B, padic_poly_degree(B) + 1, one, ctx);


        _padic_poly_div_eucl(R, Q, A, B, ctx); // A = BQ + R

        padic_poly_mul(cache, B, Q, ctx);
        padic_poly_add(cache, cache, R, ctx); // Calcule BQ + R
        
        printf("A = ");
        padic_poly_print(A, ctx);
        printf("\n");

        printf("B = ");
        padic_poly_print(B, ctx);
        printf("\n");
        
        printf("R = ");
        padic_poly_print(R, ctx);
        printf("\n");

        printf("Q = ");
        padic_poly_print(Q, ctx);
        printf("\n");

        printf("BQ + R= ");
        padic_poly_print(cache, ctx);
        printf("\n");

        printf("A = BQ + R ? %d\n", padic_poly_equal(A, cache));
        // printf("deg R < deg B ? %d\n", padic_poly_degree(R= <))
    }

    fmpz_clear(deux);
    padic_ctx_clear(ctx);
    padic_poly_clear(A);
    padic_poly_clear(B);
    padic_poly_clear(Q);
    padic_poly_clear(R);
    padic_poly_clear(cache);
    flint_randclear(state);
}