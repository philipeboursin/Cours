#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>


//------
// Renvoie f(X) avec comme argument f(X^2). La précision du résultat est la précision de P
void precompoX2(padic_poly_t P, padic_poly_t Q, padic_ctx_t C);
// Renvoie f(-X) avec comme argument f(X). La précision du résultat est la précision de P
void CompMoinsX(padic_poly_t P, padic_poly_t Q, padic_ctx_t C);
// Multiplie Q par 2^n, n \in Z
void Mul2n(padic_poly_t P, padic_poly_t Q, int n, padic_ctx_t C);
// Teichmuller increment
void TechModIncre(padic_poly_t delta, padic_poly_t M0, padic_poly_t M1, padic_poly_t V, int N, padic_ctx_t C);
// Teichmuller modulus
void TeichmullerModulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C);
// Procédure de test de precompoX2
void test1(padic_ctx_t C);
// Procédure de test de CompMoinsX
void test2(padic_ctx_t C);
// Procédure de test de Mul2n
void test3(padic_ctx_t C);
// Procédure de test de TeichmullerModulus
void test(padic_ctx_t C);


//------
void CompMoinsX(padic_poly_t P, padic_poly_t Q, padic_ctx_t C)
{
    int N = padic_poly_prec(Q);
    int deg = padic_poly_degree(Q);

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

void precompoX2(padic_poly_t P, padic_poly_t Q, padic_ctx_t C)
{
    int N = padic_poly_prec(Q);
    int deg = padic_poly_degree(Q);

    padic_t padic_temp;
    padic_poly_t padic_poly_temp;

    padic_init2(padic_temp, N);
    padic_poly_init2(padic_poly_temp, (deg + 1)/2, N);

    for (int i = 0; i < deg + 1; i = i + 2)
    {
        padic_poly_get_coeff_padic(padic_temp, Q, i, C);
        padic_poly_set_coeff_padic(padic_poly_temp, i/2, padic_temp, C);
    }

    _padic_poly_set_length(P, (deg + 1)/2);
    padic_poly_set(P, padic_poly_temp, C);

    padic_poly_clear(padic_poly_temp);
    padic_clear(padic_temp);
}

void Mul2n(padic_poly_t P, padic_poly_t Q, int n, padic_ctx_t C)
{
    int N = padic_poly_prec(Q);

    padic_t deux_pow_n;

    padic_init2(deux_pow_n, N);
    padic_set_ui(deux_pow_n, 2, C);
    padic_pow_si(deux_pow_n, deux_pow_n, n, C);
    padic_poly_scalar_mul_padic(P, Q, deux_pow_n, C);

    padic_clear(deux_pow_n);
}

void TechModIncre(padic_poly_t delta, padic_poly_t M0, padic_poly_t M1, padic_poly_t V, int N, padic_ctx_t C)
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
        int Nr = (N >> 1) + (N & 1); // partie entiere superieure de N/2
        padic_poly_t deltar;
        padic_poly_init2(deltar, 0, Nr);
        TechModIncre(deltar, M0, M1, V, Nr, C);
        

        // definition de delta0
        padic_poly_t delta0;

        padic_poly_init2(delta0, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, deltar, C);
        CompMoinsX(P2, P1, C);
        padic_poly_add(P1, P1, P2, C);
        Mul2n(delta0, P1, -1, C);
        precompoX2(delta0, delta0, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);

        // definition de delta1
        padic_poly_t delta1;

        padic_poly_init2(delta1, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, deltar, C);
        CompMoinsX(P2, P1, C);
        padic_poly_sub(P1, P1, P2, C);
        Mul2n(delta1, P1, -1, C);
        padic_poly_shift_right(delta1, delta1, 1, C); // division par X
        precompoX2(delta1, delta1, C);

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
        Mul2n(P1, P1, 1, C);
        padic_poly_sub(P1, deltar, P1, C);
        padic_poly_add(P1, V, P1, C);
        Mul2n(Vr, P1, -Nr, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de Delta
        padic_poly_t Delta;

        padic_poly_init2(Delta, 0, N - Nr);

        TechModIncre(Delta, M0, M1, Vr, N - Nr, C);

        // definition de delta
        padic_poly_init2(P1, 0, N);

        padic_poly_set(P1, Delta, C);
        Mul2n(P1, P1, Nr, C);
        padic_poly_add(delta, deltar, P1, C);

        padic_poly_clear(P1);

        // clear des différentes variables
        padic_poly_clear(delta0);
        padic_poly_clear(delta1);
        padic_poly_clear(Vr);
        padic_poly_clear(Delta);
    }
}

void TeichmullerModulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C)
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
        int Nr = (N >> 1) + (N & 1); // partie entiere sup de N/2
        padic_poly_t Mr;
        padic_poly_init2(Mr, 0, Nr);
        TeichmullerModulus(Mr, m, Nr, C);

        // definition de M0
        padic_poly_t M0;

        padic_poly_init2(M0, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, Mr, C); // Augmentation de la précision de M en prévision de la division par 2
        CompMoinsX(P2, P1, C);
        padic_poly_add(P1, P1, P2, C);
        Mul2n(M0, P1, -1, C);
        precompoX2(M0, M0, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de M1
        padic_poly_t M1;

        padic_poly_init2(M1, 0, N);
        padic_poly_init2(P1, 0, N + 1);
        padic_poly_init2(P2, 0, N + 1);

        padic_poly_set(P1, Mr, C);
        CompMoinsX(P2, P1, C);
        padic_poly_sub(P1, P1, P2, C);
        Mul2n(M1, P1, -1, C);
        padic_poly_shift_right(M1, M1, 1, C); // division par X
        precompoX2(M1, M1, C);

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
        Mul2n(V, P1, -Nr, C);

        padic_poly_clear(P1);
        padic_poly_clear(P2);


        // definition de delta
        padic_poly_t delta;
        padic_poly_init2(delta, 0, N - Nr);
        TechModIncre(delta, M0, M1, V, N - Nr, C);


        //definition de M
        padic_poly_init2(P1, 0, N);

        padic_poly_set(P1, delta, C);
        Mul2n(P1, P1, Nr, C);
        padic_poly_add(M, Mr, P1, C);

        padic_poly_clear(P1);


        //------
        // printf("N : %d\n", N);
        // printf("M0 : ");
        // padic_poly_print(M0, C);
        // printf("\n");
        // printf("M1 : ");
        // padic_poly_print(M1, C);
        // printf("\n");
        // printf("V : ");
        // padic_poly_print(V, C);
        // printf("\n");
        // printf("delta : ");
        // padic_poly_print(delta, C);
        // printf("\n");


        // clear des variables 
        padic_poly_clear(Mr);
        padic_poly_clear(M0);
        padic_poly_clear(M1);
        padic_poly_clear(V);
        padic_poly_clear(delta);

    }

    // printf("M : ");
    // padic_poly_print(M, C);
    // printf("\n------------------------------------------------------------------------\n");
}

void test1(padic_ctx_t C)
{
    padic_poly_t f;
    padic_t un;
    
    padic_poly_init2(f, 5, 2);
    padic_init2(un, 2);
    padic_one(un);

    padic_poly_set_coeff_padic(f, 0, un, C);
    padic_poly_set_coeff_padic(f, 4, un, C);
    
    padic_poly_print(f, C);
    printf("\n");
    precompoX2(f, f, C);
    padic_poly_print(f, C);
    printf("\n");

    padic_poly_clear(f);
    padic_clear(un);
}

void test2(padic_ctx_t C)
{
    padic_poly_t m;
    padic_poly_t M;
    padic_t un;
    int N = 1;
    
    padic_poly_init2(m, 9, N);
    padic_poly_init2(M, 9, N);
    padic_init(un);
    padic_one(un);

    padic_poly_set_coeff_padic(m, 0, un, C);
    padic_poly_set_coeff_padic(m, 2, un, C);
    padic_poly_set_coeff_padic(m, 3, un, C);
    padic_poly_set_coeff_padic(m, 4, un, C);
    padic_poly_set_coeff_padic(m, 8, un, C);

    CompMoinsX(M, m, C);

    padic_poly_print(M, C);
    printf("\n");

    padic_poly_clear(m);
    padic_poly_clear(M);
    padic_clear(un);
}

void test3(padic_ctx_t C)
{
    padic_poly_t m;
    padic_t deux;
    int N = 2;
    
    padic_poly_init2(m, 9, N);
    padic_init2(deux, N);

    padic_set_ui(deux, 2, C);

    padic_poly_set_coeff_padic(m, 0, deux, C);
    padic_poly_set_coeff_padic(m, 2, deux, C);
    padic_poly_set_coeff_padic(m, 3, deux, C);
    padic_poly_set_coeff_padic(m, 4, deux, C);
    padic_poly_set_coeff_padic(m, 8, deux, C);

    Mul2n(m, m, 1, C);

    padic_poly_print(m, C);
    printf("\n");

    padic_poly_clear(m);
    padic_clear(deux);
}

void test(padic_ctx_t C)
{
    padic_poly_t m;
    padic_poly_t M;
    padic_t un;
    int N = 10;
    
    padic_poly_init2(m, 9, 1);
    padic_poly_init2(M, 0, N);
    padic_init2(un, 1);
    padic_one(un);

    padic_poly_set_coeff_padic(m, 0, un, C);
    padic_poly_set_coeff_padic(m, 2, un, C);
    padic_poly_set_coeff_padic(m, 3, un, C);
    padic_poly_set_coeff_padic(m, 4, un, C);
    padic_poly_set_coeff_padic(m, 8, un, C);

    TeichmullerModulus(M, m, N, C);

    padic_poly_print(M, C);
    printf("\n");

    padic_poly_clear(m);
    padic_poly_clear(M);
    padic_clear(un);
}


//------
void main()
{
    // Initialisation du contexte
    fmpz_t p;
    padic_ctx_t C;
    fmpz_init_set_si(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_TERSE);

    // Tests
    // test1(C);
    // test2(C);
    // test3(C);
    test(C);

    fmpz_clear(p);
    padic_ctx_clear(C);
}