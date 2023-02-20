#include "zqadic.h"

int main()
{
    printf("-------------------- TEST DE zqadic_reduce --------------------\n");
    
    slong prec = 10;

    fmpz_t deux;
    zqadic_ctx_t ctx;
    padic_ctx_t pctx;
    fmpz_poly_t m, a, b;
    padic_poly_t R, Q, A, B;
    padic_poly_t cache;
    flint_rand_t state;
    padic_t one;
    
    fmpz_poly_init(m);
    fmpz_poly_init(a);
    fmpz_poly_init(b);
    padic_poly_init2(R, 0, prec);
    padic_poly_init2(Q, 0, prec);
    padic_poly_init2(A, 15, prec);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    fmpz_poly_set_coeff_si(a, 0, 168);
    fmpz_poly_set_coeff_si(a, 1, 428);
    fmpz_poly_set_coeff_si(a, 2, 646);
    fmpz_poly_set_coeff_si(a, 3, 148);
    fmpz_poly_set_coeff_si(a, 4, 313);
    fmpz_poly_set_coeff_si(a, 5, 214);
    fmpz_poly_set_coeff_si(a, 6, 452);
    fmpz_poly_set_coeff_si(a, 7, 776);
    fmpz_poly_set_coeff_si(a, 8, 922);
    fmpz_poly_set_coeff_si(a, 9, 375);
    fmpz_poly_set_coeff_si(a, 10, 133);
    fmpz_poly_set_coeff_si(a, 11, 684);
    fmpz_poly_set_coeff_si(a, 12, 763);
    fmpz_poly_set_coeff_si(a, 13, 781);
    fmpz_poly_set_coeff_si(a, 14, 559);

    _zqadic_ctx_init_teichmuller(ctx, m, prec, 0, prec, PADIC_TERSE);
    
    padic_poly_set_fmpz_poly(A, a, ctx -> pctx);

    printf("Test du handbook, page 246 :\n");
    printf("A = ");
    padic_poly_print(A, ctx -> pctx);
    printf("\n");
    printf("M = ");
    padic_poly_print(ctx -> M, ctx -> pctx);
    printf("\n");

    padic_poly_eucl_div(R, Q, A, ctx -> M, ctx -> pctx);
    
    printf("R = ");
    padic_poly_print(R, ctx -> pctx);
    printf("\n");
    printf("Q = ");
    padic_poly_print(Q, ctx -> pctx);
    printf("\n");


    int check = 1;
    int N = 1000;
    printf("On réalise %d fois la division euclidienne de A par B pris au hasard. Si le test est passé, affiche 1, sinon 0.\n", N);
    
    padic_init2(one, prec);
    fmpz_init_set_ui(deux, 2);  
    padic_ctx_init(pctx, deux, 0, prec, PADIC_TERSE);
    padic_poly_init2(B, 5, prec);
    padic_poly_init2(cache, 0, prec);
    padic_one(one);
    flint_randinit(state);


    for (int i = 0; i < N; i++)
    {
        padic_poly_randtest(A, state, 15, pctx);
        padic_poly_randtest(B, state, 5, pctx);
        padic_poly_set_coeff_padic(B, padic_poly_degree(B) + 1, one, pctx);

        padic_poly_eucl_div(R, Q, A, B, pctx); // A = BQ + R

        padic_poly_mul(cache, B, Q, pctx);
        padic_poly_add(cache, cache, R, pctx); // Calcule BQ + R

        if (padic_poly_equal(cache, A) != 1) check = 0;        
    }

    printf("%d\n", check);

    fmpz_clear(deux);
    padic_ctx_clear(pctx);
    padic_poly_clear(cache);
    flint_randclear(state);
    fmpz_poly_clear(m);
    fmpz_poly_clear(a);
    fmpz_poly_clear(b);
    padic_poly_clear(R);
    padic_poly_clear(Q);
    padic_poly_clear(A);
    padic_poly_clear(B);
    zqadic_ctx_clear(ctx);
}