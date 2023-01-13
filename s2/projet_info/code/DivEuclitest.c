#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>


void RedModXn(padic_poly_t P, padic_poly_t Q, int n, padic_ctx_t C) // Procédure qui transfomre P en Q mod X^n
{
    int deg = padic_poly_degree(Q);
    if (deg<n)
    {
        padic_poly_set(P,Q,C);
    }
    else
    {
         
        int N=padic_poly_prec(Q);
        padic_t padic_cache;
        padic_init2(padic_cache, N);

        for (int i = 0; i < n; i++) // deg>=n
        {
            padic_poly_get_coeff_padic(padic_cache, Q, i, C);
            padic_poly_set_coeff_padic(P, i, padic_cache, C);
        }
        padic_clear(padic_cache);
    }

}


void CoefRenv(padic_poly_t P, padic_poly_t Q, padic_ctx_t C) // Procédure qui transforme P en un polynôme dont les coefficients sont ceux de Q renversés
{
    int deg = padic_poly_degree(Q);
    int N = padic_poly_prec(Q);

    padic_t padic_cache;
    padic_init2(padic_cache, N);

    for (int i = 0; i < deg+1; i++)
    {
        padic_poly_get_coeff_padic(padic_cache, Q, i, C);
        padic_poly_set_coeff_padic(P, deg-i, padic_cache, C);
    }

    padic_clear(padic_cache);
}


void DivEucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C ) // Procédure qui attribue à R (resp Q) la valeur du reste (resp quotient) de la div de A par B (supposé unitaire)
{
    int degA = padic_poly_degree(A);
    int degB = padic_poly_degree(B);
    int N = padic_poly_prec(B);

    if (degA<degB)
    {
        
        padic_poly_set(R,A,C);
        padic_poly_zero(Q);
    }
    else
    {
        int n =degA-degB+1;

        padic_poly_t P1 ; //polynômes variables caches
        padic_poly_t P2 ;
        padic_poly_t P3 ;
        padic_t padic_cache;

        padic_poly_init2(P1, degB, N);
        padic_poly_init2(P2, degB, N);
        padic_poly_init2(P3,n,N);

        CoefRenv(P2,B,C);
        padic_poly_inv_series(P1,P2,n,C); // P1=c dans le livre
        //padic_poly_print(P1,C);  donne la bonne chose
        //printf("\n");

        padic_poly_init2(P2, degA, N);
        CoefRenv(P2,A,C);
        padic_poly_mul(P3, P1, P2, C);
        padic_poly_clear(P1);
        padic_poly_init2(P1, n, N);
        RedModXn(P1,P3,n,C); // P1=\tilde{q}
        //padic_poly_print(P1,C); donne la bonne chose
        //printf("\n");

        
        padic_poly_clear(P2);
        padic_poly_init2(P2, n, N);
        padic_init2(padic_cache, N);
        int d = padic_poly_degree(P1);
        int borne;
        if (d<n)
        {
            borne=d;
        }
        else
        {
            borne=n;
        }
        
        

        for (int i = 0; i < borne; i++) // on ne prend que les n premiers coefs de \tilde{q}=P3
        {
            padic_poly_get_coeff_padic(padic_cache, P1, borne-i, C);           
            padic_poly_set_coeff_padic(P2, i, padic_cache, C); // P2 = q dans le livre
        }
        
        padic_poly_set(Q,P2,C); // on a bien définit q


        padic_poly_mul(P1,B,P2,C);
        padic_poly_sub(P3,A,P1,C); // P3= a-bq
        RedModXn(R,P3,degB,C); // on a bien définit r

        padic_poly_clear(P3);
        padic_poly_clear(P2);
        padic_poly_clear(P1);
        padic_clear(padic_cache);



    }
    


}


void polytesta(padic_poly_t B, padic_ctx_t C)
{
    padic_t a0;
    padic_init(a0);
    padic_set_si(a0, 168, C);
    padic_poly_set_coeff_padic(B, 0, a0, C);
    padic_t a1;
    padic_init(a1);
    padic_set_si(a1, 428, C);
    padic_poly_set_coeff_padic(B, 1, a1, C);
    padic_t a2;
    padic_init(a2);
    padic_set_si(a2, 646, C);
    padic_poly_set_coeff_padic(B, 2, a2, C);
    padic_t a3;
    padic_init(a3);
    padic_set_si(a3, 148, C);
    padic_poly_set_coeff_padic(B, 3, a3, C);
    padic_t a4;
    padic_init(a4);
    padic_set_si(a4, 313, C);
    padic_poly_set_coeff_padic(B, 4, a4, C);
    padic_t a5;
    padic_init(a5);
    padic_set_si(a5, 214, C);
    padic_poly_set_coeff_padic(B, 5, a5, C);
    padic_t a6;
    padic_init(a6);
    padic_set_si(a6, 452, C);
    padic_poly_set_coeff_padic(B, 6, a6, C);
    padic_t a7;
    padic_init(a7);
    padic_set_si(a7, 776, C);
    padic_poly_set_coeff_padic(B, 7, a7, C);
    padic_t a8;
    padic_init(a8);
    padic_set_si(a8, 922, C);
    padic_poly_set_coeff_padic(B, 8, a8, C);
    padic_t a9;
    padic_init(a9);
    padic_set_si(a9,375, C);
    padic_poly_set_coeff_padic(B, 9, a9, C);
    padic_t a10;
    padic_init(a10);
    padic_set_si(a10, 133, C);
    padic_poly_set_coeff_padic(B,10, a10, C);
    padic_t a11;
    padic_init(a11);
    padic_set_si(a11, 684, C);
    padic_poly_set_coeff_padic(B, 11, a11, C);
    padic_t a12;
    padic_init(a12);
    padic_set_si(a12, 763, C);
    padic_poly_set_coeff_padic(B, 12, a12, C);
    padic_t a13;
    padic_init(a13);
    padic_set_si(a13, 781, C);
    padic_poly_set_coeff_padic(B, 13, a13, C);
    padic_t a14;
    padic_init(a14);
    padic_set_si(a14, 559, C);
    padic_poly_set_coeff_padic(B, 14, a14, C);
}


void polytestb(padic_poly_t B, padic_ctx_t C)
{
    padic_t a0;
    padic_init(a0);
    padic_set_si(a0, 1, C);
    padic_poly_set_coeff_padic(B, 0, a0, C);
    padic_t a1;
    padic_init(a1);
    padic_set_si(a1, 562, C);
    padic_poly_set_coeff_padic(B, 1, a1, C);
    padic_t a2;
    padic_init(a2);
    padic_set_si(a2, 1019, C);
    padic_poly_set_coeff_padic(B, 2, a2, C);
    padic_t a3;
    padic_init(a3);
    padic_set_si(a3, 21, C);
    padic_poly_set_coeff_padic(B, 3, a3, C);
    padic_t a4;
    padic_init(a4);
    padic_set_si(a4, 523, C);
    padic_poly_set_coeff_padic(B, 4, a4, C);
    padic_t a5;
    padic_init(a5);
    padic_set_si(a5, 134, C);
    padic_poly_set_coeff_padic(B, 5, a5, C);
    padic_t a6;
    padic_init(a6);
    padic_set_si(a6, 842, C);
    padic_poly_set_coeff_padic(B, 6, a6, C);
    padic_t a7;
    padic_init(a7);
    padic_set_si(a7, 644, C);
    padic_poly_set_coeff_padic(B, 7, a7, C);
    padic_t a8;
    padic_init(a8);
    padic_set_si(a8, 1, C);
    padic_poly_set_coeff_padic(B, 8, a8, C);
}


void main()
{
    
    // Initialisation du contexte
    fmpz_t p;
    padic_ctx_t C;
    fmpz_init_set_si(p, 2);
    padic_ctx_init(C, p, 0, 10, PADIC_TERSE);

    padic_poly_t a;
    padic_poly_t b;
    padic_poly_init2(a,14,10);
    padic_poly_init2(b,8,10);
    polytesta(a,C);
    polytestb(b,C);

    padic_poly_t R;
    padic_poly_t Q;
    padic_poly_init2(R,8,10);
    padic_poly_init2(Q,8,10);

    DivEucl(a,b,R,Q,C);

    
    padic_poly_print(a,C);
    printf("\n");
    padic_poly_print(b,C);
    printf("\n");
    padic_poly_print(R,C);
    printf("\n");
    padic_poly_print(Q,C);
    printf("\n");

    padic_poly_clear(a);
    padic_poly_clear(b);
    padic_poly_clear(R);
    padic_poly_clear(Q);
    padic_ctx_clear(C);
   

}