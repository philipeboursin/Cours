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


void RedMod(padic_poly_t A, padic_poly_t mod, padic_poly_t R, padic_ctx_t C ) // R prend la valeur du reste de A par mod
{
    padic_poly_t Cache1 ;
    padic_poly_init(Cache1);
    DivEucl(A,mod,R,Cache1,C);
    padic_poly_clear(Cache1);

}

void multZq(padic_poly_t M, padic_poly_t A, padic_poly_t B, padic_poly_t mod, padic_ctx_t C,) // On suppose que A et B sont réduit
{
    padic_poly_t cache;
    padic_poly_init(cache);
    padic_poly_mul(cache,A,B,C);
    RedMod(cache,mod,M,C)

}





void main()
{
    
    // Initialisation du contexte
    fmpz_t p;
    padic_ctx_t C;
    fmpz_init_set_si(p, 2);
    padic_ctx_init(C, p, 0, 20, PADIC_SERIES);

    

}