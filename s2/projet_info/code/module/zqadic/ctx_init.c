#include "zqadic.h"

void _comp_moins_x(padic_poly_t P, padic_poly_t Q, padic_ctx_t C)
{
    slong N = padic_poly_prec(Q);

    padic_t moins_un;
    padic_poly_t moins_X;

    padic_init2(moins_un, N);
    padic_poly_init2(moins_X, 2, N);

    padic_one(moins_un);
    padic_neg(moins_un, moins_un, C);
    padic_poly_set_coeff_padic(moins_X, 1, moins_un, C);
    padic_poly_compose(P, Q, moins_X, C);

    padic_clear(moins_un);
    padic_poly_clear(moins_X);
}

void _precomp_x2(padic_poly_t P, padic_poly_t Q, padic_ctx_t C)
{
    slong N = padic_poly_prec(Q);
    slong deg = padic_poly_degree(Q);

    padic_t padic_temp;
    padic_poly_t padic_poly_temp;

    padic_init2(padic_temp, N);
    padic_poly_init2(padic_poly_temp, (deg + 1)/2, N);

    for (slong i = 0; i < deg + 1; i = i + 2)
    {
        padic_poly_get_coeff_padic(padic_temp, Q, i, C);
        padic_poly_set_coeff_padic(padic_poly_temp, i/2, padic_temp, C);
    }

    _padic_poly_set_length(P, (deg + 1)/2);
    padic_poly_set(P, padic_poly_temp, C);

    padic_poly_clear(padic_poly_temp);
    padic_clear(padic_temp);
}

void _mul_2n(padic_poly_t P, padic_poly_t Q, slong n, padic_ctx_t C)
{
    slong N = padic_poly_prec(Q);

    padic_t deux_pow_n;

    padic_init2(deux_pow_n, N);
    padic_set_ui(deux_pow_n, 2, C);
    padic_pow_si(deux_pow_n, deux_pow_n, n, C);
    padic_poly_scalar_mul_padic(P, Q, deux_pow_n, C);

    padic_clear(deux_pow_n);
}

void _teichmuller_modulus_increment(padic_poly_t delta, padic_poly_t M0, padic_poly_t M1, padic_poly_t V, slong N, padic_ctx_t C)
{
    if (N == 1)
    {
        padic_poly_neg(delta, V, C);
    }
    else
    {
        // variables cache
        padic_poly_t P1;
        padic_poly_t P2;

        //------ Algo
        slong Nr = (N >> 1) + (N & 1); // partie entiere superieure de N/2
        padic_poly_t deltar;
        padic_poly_init2(deltar, 0, Nr);
        _teichmuller_modulus_increment(deltar, M0, M1, V, Nr, C);
        

        // definition de delta0
        padic_poly_t delta0;

        padic_poly_init2(delta0, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, deltar, C);
        _comp_moins_x(P2, P1, C);
        padic_poly_add(P1, P1, P2, C);
        _mul_2n(delta0, P1, -1, C);
        _precomp_x2(delta0, delta0, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);

        // definition de delta1
        padic_poly_t delta1;

        padic_poly_init2(delta1, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, deltar, C);
        _comp_moins_x(P2, P1, C);
        padic_poly_sub(P1, P1, P2, C);
        _mul_2n(delta1, P1, -1, C);
        padic_poly_shift_right(delta1, delta1, 1, C); // division par X
        _precomp_x2(delta1, delta1, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);

        // definition Vr
        padic_poly_t Vr;

        padic_poly_init2(Vr, 0, N - Nr);
        padic_poly_init2(P1, 0, N);
        padic_poly_init2(P2, 0, N);

        padic_poly_mul(P1, M0, delta0, C);
        padic_poly_mul(P2, M1, delta1, C);
        padic_poly_shift_left(P2, P2, 1, C);
        padic_poly_sub(P1, P1, P2, C);
        _mul_2n(P1, P1, 1, C);
        padic_poly_sub(P1, deltar, P1, C);
        padic_poly_add(P1, V, P1, C);
        _mul_2n(Vr, P1, -Nr, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de Delta
        padic_poly_t Delta;

        padic_poly_init2(Delta, 0, N - Nr);

        _teichmuller_modulus_increment(Delta, M0, M1, Vr, N - Nr, C);

        // definition de delta
        padic_poly_init2(P1, 0, N);

        padic_poly_set(P1, Delta, C);
        _mul_2n(P1, P1, Nr, C);
        padic_poly_add(delta, deltar, P1, C);

        padic_poly_clear(P1);

        // clear des différentes variables
        padic_poly_clear(delta0);
        padic_poly_clear(delta1);
        padic_poly_clear(Vr);
        padic_poly_clear(Delta);
        padic_poly_clear(deltar);
    }
}

void _teichmuller_modulus_auxi(padic_poly_t M, padic_poly_t m, slong N, padic_ctx_t C)
{
    if (N == 1)
    {
        padic_poly_set(M, m, C);
    }
    else
    {
        // variables cache
        padic_poly_t P1;
        padic_poly_t P2;

        //------ Algo
        slong Nr = (N >> 1) + (N & 1); // partie entiere sup de N/2
        padic_poly_t Mr;
        padic_poly_init2(Mr, 0, Nr);
        _teichmuller_modulus_auxi(Mr, m, Nr, C);

        // definition de M0
        padic_poly_t M0;

        padic_poly_init2(M0, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, Mr, C); // Augmentation de la précision de M en prévision de la division par 2
        _comp_moins_x(P2, P1, C);
        padic_poly_add(P1, P1, P2, C);
        _mul_2n(M0, P1, -1, C);
        _precomp_x2(M0, M0, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de M1
        padic_poly_t M1;

        padic_poly_init2(M1, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, Mr, C);
        _comp_moins_x(P2, P1, C);
        padic_poly_sub(P1, P1, P2, C);
        _mul_2n(M1, P1, -1, C);
        padic_poly_shift_right(M1, M1, 1, C); // division par X
        _precomp_x2(M1, M1, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de V
        padic_poly_t V;

        padic_poly_init2(V, 0, N - Nr);
        padic_poly_init2(P1, 0, N);
        padic_poly_init2(P2, 0, N);

        padic_poly_mul(P1, M1, M1, C);
        padic_poly_shift_left(P1, P1, 1, C);
        padic_poly_mul(P2, M0, M0, C);
        padic_poly_add(P1, P1, Mr, C);
        padic_poly_sub(P1, P1, P2, C);        
        _mul_2n(V, P1, -Nr, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de delta
        padic_poly_t delta;
        padic_poly_init2(delta, 0, N - Nr);
        _teichmuller_modulus_increment(delta, M0, M1, V, N - Nr, C);


        //definition de M
        padic_poly_init2(P1, 0, N);

        padic_poly_set(P1, delta, C);
        _mul_2n(P1, P1, Nr, C);
        padic_poly_add(M, Mr, P1, C);

        padic_poly_clear(P1);


        // clear des variables 
        padic_poly_clear(Mr);
        padic_poly_clear(M0);
        padic_poly_clear(M1);
        padic_poly_clear(V);
        padic_poly_clear(delta);
    }
}

void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, slong N, padic_ctx_t C)
{
    _teichmuller_modulus_auxi(M, m, N, C);
    if ((padic_poly_degree(m) % 2) == 1) padic_poly_neg(M, M, C);
}

void _cj_precomputation(zqadic_t** pC, zqadic_ctx_t ctx)
{
    slong p = fmpz_get_si(ctx -> p);
    slong deg = ctx -> deg;
    slong prec = ctx -> prec;

    fmpz_t e; // p^(d - 1)
    zqadic_t C_1; // X^(p^(d - 1))
    zqadic_t C_j; // C_j
    fmpz_poly_t f;

    fmpz_init_set_ui(e, n_pow(p, deg - 1)); // e = p^(d - 1)
    zqadic_init(C_1, ctx);
    zqadic_init(C_j, ctx);
    fmpz_poly_init(f);
    fmpz_poly_set_coeff_si(f, 1, 1);
    zqadic_set_fmpz_poly(C_1, f, ctx); // C_1 contient X
    zqadic_pow(C_1, C_1, e, ctx); // C_1 contient X^e
    zqadic_one(C_j); // C_j contient 1

    *pC = (zqadic_t*) malloc(p*sizeof(zqadic_t)); // Tableau d'adresses pour les C_j
    for (slong j = 0; j < p; j++)
    {
        zqadic_init2((*pC)[j], prec, ctx);
        zqadic_set((*pC)[j], C_j, ctx);
        zqadic_mul(C_j, C_j, C_1, ctx);
    }

    fmpz_clear(e);
    zqadic_clear(C_1);
    zqadic_clear(C_j);
    fmpz_poly_clear(f);
}

void zqadic_ctx_init_padic_poly(zqadic_ctx_t zqadic_ctx, padic_poly_t M, padic_ctx_t padic_ctx, enum rep_type type)
{
    zqadic_ctx -> prec = padic_poly_prec(M);
    zqadic_ctx -> deg = padic_poly_degree(M);
    zqadic_ctx -> type = type;
    fmpz_init_set(zqadic_ctx -> p, padic_ctx -> p);
    padic_ctx_init(zqadic_ctx -> pctx, padic_ctx -> p, padic_ctx -> min, padic_ctx -> max, padic_ctx -> mode);
    padic_poly_init2(zqadic_ctx -> M, padic_poly_degree(M) + 1, padic_poly_prec(M));
    padic_poly_set(zqadic_ctx -> M, M, padic_ctx);
    _cj_precomputation(&(zqadic_ctx -> C), zqadic_ctx);
}

void _zqadic_ctx_init_teichmuller(zqadic_ctx_t zqadic_ctx, fmpz_poly_t m, slong prec, slong min, slong max, enum padic_print_mode mode)
{
    padic_poly_t lift;
    fmpz_t deux;
    padic_ctx_t padic_ctx;
    padic_poly_t M;

    fmpz_init_set_ui(deux, 2);
    padic_ctx_init(padic_ctx, deux, min, max, mode);

    padic_poly_init2(lift, fmpz_poly_degree(m) + 1, 1);
    padic_poly_set_fmpz_poly(lift, m, padic_ctx);

    padic_poly_init2(M, padic_poly_degree(lift), prec);
    _teichmuller_modulus(M, lift, prec, padic_ctx);
    zqadic_ctx_init_padic_poly(zqadic_ctx, M, padic_ctx, TEICHMULLER);
    
    padic_poly_clear(M);
    padic_ctx_clear(padic_ctx);
    padic_poly_clear(lift);
    fmpz_clear(deux);
}

void zqadic_ctx_init_teichmuller(zqadic_ctx_t zqadic_ctx, slong deg, slong prec, slong min, slong max, enum padic_print_mode mode)
{
    fmpz_poly_t m;
    fmpz_mod_ctx_t ctx_mod;
    fmpz_mod_poly_t m_modp;
    flint_rand_t state;
    fmpz_t deux;

    fmpz_init_set_ui(deux, 2);
    fmpz_mod_ctx_init(ctx_mod, deux);
    fmpz_mod_poly_init(m_modp, ctx_mod);
    flint_randinit(state);
    fmpz_poly_init(m);

    fmpz_mod_poly_randtest_sparse_irreducible(m_modp, state, deg + 1, ctx_mod);
    fmpz_mod_poly_get_fmpz_poly(m, m_modp, ctx_mod);

    _zqadic_ctx_init_teichmuller(zqadic_ctx, m, prec, min, max, mode);

    fmpz_poly_clear(m);
    fmpz_mod_poly_clear(m_modp, ctx_mod);
    fmpz_mod_ctx_clear(ctx_mod);
    flint_randclear(state);
    fmpz_clear(deux);
}

void _zqadic_ctx_init(zqadic_ctx_t zqadic_ctx, fmpz_poly_t m, fmpz_t p, slong prec, slong min, slong max, enum padic_print_mode mode)
{
    padic_poly_t lift;
    padic_ctx_t padic_ctx;

    padic_ctx_init(padic_ctx, p, min, max, mode);

    padic_poly_init2(lift, fmpz_poly_degree(m) + 1, prec);
    padic_poly_set_fmpz_poly(lift, m, padic_ctx);

    zqadic_ctx_init_padic_poly(zqadic_ctx, lift, padic_ctx, SPARSE);
    
    padic_ctx_clear(padic_ctx);
    padic_poly_clear(lift);
}

void zqadic_ctx_init(zqadic_ctx_t zqadic_ctx, fmpz_t p, slong deg, slong prec, slong min, slong max, enum padic_print_mode mode)
{
    fmpz_poly_t m;
    fmpz_mod_ctx_t ctx_mod;
    fmpz_mod_poly_t m_modp;
    flint_rand_t state;

    fmpz_mod_ctx_init(ctx_mod, p);
    fmpz_mod_poly_init(m_modp, ctx_mod);
    flint_randinit(state);
    fmpz_poly_init(m);

    fmpz_mod_poly_randtest_sparse_irreducible(m_modp, state, deg + 1, ctx_mod);
    fmpz_mod_poly_get_fmpz_poly(m, m_modp, ctx_mod);

    _zqadic_ctx_init(zqadic_ctx, m, p, prec, min, max, mode);

    fmpz_poly_clear(m);
    fmpz_mod_poly_clear(m_modp, ctx_mod);
    fmpz_mod_ctx_clear(ctx_mod);
    flint_randclear(state);
}