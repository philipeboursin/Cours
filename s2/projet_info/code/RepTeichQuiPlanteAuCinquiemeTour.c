#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>




void main()
{

//  ----------------on initialise les premières constantes et le context


fmpz_t p; // le nb premier en question
fmpz_init_set_si(p,2);


padic_ctx_t C;
int prec=20; // la précision 2-adique
padic_ctx_init(C, p, 0, prec, PADIC_SERIES); 


padic_t un;
padic_init(un);
padic_one(un);
padic_t deux;
padic_init(deux);
padic_add(deux, un, un, C);
padic_t un_demi; 
padic_init(un_demi);
padic_inv(un_demi, deux, C);

padic_poly_t P;
    padic_poly_init2(P,9,1);

    padic_t a0;
    padic_init(a0);
    fmpz_t a00;
    fmpz_init_set_ui(a00, 1);
    padic_set_fmpz(a0, a00, C);

    padic_t a2;
    padic_init(a2);   
    fmpz_t a20;
    fmpz_init_set_ui(a20, 1);
    padic_set_fmpz(a2, a20, C);
    
    padic_t a3; 
    padic_init(a3);  
    fmpz_t a30;
    fmpz_init_set_ui(a30, 1);
    padic_set_fmpz(a3, a30, C);
    
    padic_t a4;
    padic_init(a4); 
    fmpz_t a40;
    fmpz_init_set_ui(a40, 1);
    padic_set_fmpz(a4, a40, C);

    padic_t a8;
    padic_init(a8); 
    fmpz_t a80;
    fmpz_init_set_ui(a80, 1);
    padic_set_fmpz(a8, a80, C);



    padic_poly_set_coeff_padic(P, 0, a0, C);
    padic_poly_set_coeff_padic(P, 2, a2, C);
    padic_poly_set_coeff_padic(P, 3, a3, C);
    padic_poly_set_coeff_padic(P, 4, a4, C);
    padic_poly_set_coeff_padic(P, 8, a8, C);





// on a besoin de construire P(-X) à partir de P(X) 

void CompomoinsX( padic_poly_t P0, padic_poly_t P1) // transforme P0(X) en P1(-X)
{
   
    padic_poly_t moinsX;
    padic_poly_init(moinsX);
    padic_t moinsun;
    padic_init(moinsun);
    padic_t a;
    padic_init(a);
    padic_one(a);
    padic_neg(moinsun,a,C);
    padic_poly_set_coeff_padic(moinsX,1,moinsun, C);
    padic_poly_compose(P0, P1, moinsX, C);

}

// on a besoin de pouvoir definir des polynomes par P(X^2)= ....  

void precompoX2( padic_poly_t P0, padic_poly_t P1) // on suppose que P1 est un polynôme ayant pour coefs non nuls que ceux devant des X^{2i} P0(X^2)<-P1(X)
{
    
    fmpz_t d ;
    fmpz_init_set_ui(d, padic_poly_degree(P1));
    int deg;
    deg=fmpz_get_si(d);

    padic_t coefs[deg+1];
    
    for (int i = 0; i < deg+1; i=i+2)
    {
        padic_init(coefs[i]);
        padic_poly_get_coeff_padic(coefs[i], P1, i, C);
        padic_poly_set_coeff_padic(P0, i/2, coefs[i], C);

    }

}


// ----------------- l'incrémentation de Teichmuller


void TechModIncre( padic_poly_t delta, padic_poly_t M0, padic_poly_t M1, padic_poly_t V, int N)

    {
        if (N==1)
        {
            padic_poly_t vmod2;
            fmpz_t d ;
            fmpz_init_set_ui(d, padic_poly_degree(V));
            int deg;
            deg=fmpz_get_si(d);
            padic_poly_init2(vmod2,deg,1);
            padic_poly_set(vmod2,V,C );

            padic_poly_neg(delta, vmod2, C);

        }
        else
        {
            int Nr = (N>>1)+(N&1)           ; // partie entiere superieur de N/2
            padic_poly_t deltar;
            padic_poly_init(deltar);
            TechModIncre(deltar,M0,M1,V,Nr);
            
            fmpz_t d ;
            fmpz_init_set_ui(d, padic_poly_degree(deltar));
            int deg;
            deg=fmpz_get_si(d);

            // definition de delta0

            padic_poly_t delta0oX2 ;
            padic_poly_init2(delta0oX2,deg+1,(1<<N));
            padic_poly_t sum;
            padic_poly_init(sum);
            padic_poly_t deltaroMX;
            padic_poly_init(deltaroMX);
            CompomoinsX(deltaroMX,deltar);
            padic_poly_add(sum, deltar, deltaroMX, C);
            padic_poly_scalar_mul_padic(delta0oX2, sum, un_demi, C);

            padic_poly_t delta0;
            padic_poly_init2(delta0,deg+1,(1<<N));
            precompoX2(delta0,delta0oX2);
            padic_poly_clear(delta0oX2);

            // definition de delta1

            padic_poly_t delta1oX2 ;
            padic_poly_init2(delta1oX2,deg+1,(1<<N));
            padic_poly_sub(sum, deltar, deltaroMX, C);
            padic_poly_t cache;
            padic_poly_init(cache);
            padic_poly_scalar_mul_padic(cache, sum, un_demi, C);
            padic_poly_shift_right(delta1oX2, cache, 1,C); // la division par X


            padic_poly_t delta1;
            padic_poly_init2(delta1,deg+1,(1<<N));
            precompoX2(delta1,delta1oX2);
            padic_poly_clear(delta1oX2);

            // definition Vr

            padic_poly_add(sum, V,deltar,C);
            
            padic_poly_t mult0;
            padic_poly_init(mult0);
            padic_poly_mul(mult0,M0,delta0,C);
            padic_poly_t mult1;
            padic_poly_init(mult1);
            padic_poly_mul(mult1,M1,delta1,C);
            padic_poly_shift_left(cache, mult1, 1,C); //cache = X*M1*delta1

            padic_poly_t sub0;
            padic_poly_init(sub0);
            padic_poly_sub(sub0,mult0,cache,C); // sub0 = M0*delta0- X*M1*delta1, et comme on a plus besoin des poly mult0, mult1, cache, on reutilise cache, on libere les aures
            padic_poly_scalar_mul_padic(cache, sub0, deux, C);
            padic_poly_clear(mult0);
            padic_poly_clear(mult1);

            padic_poly_t numerateur;
            padic_poly_init(numerateur);
            padic_poly_sub(numerateur, sum, cache,C );
            padic_poly_clear(sum);
            padic_poly_clear(sub0);

            padic_t un_demiexpNr;
            padic_init(un_demiexpNr);
            padic_pow_si(un_demiexpNr, un_demi, Nr, C);

            padic_poly_t Vr;
            padic_poly_init2(Vr,deg,(1<<(N-Nr)));
            padic_poly_scalar_mul_padic(Vr, numerateur, un_demiexpNr, C);
            padic_poly_clear(numerateur);

            //definition de Delta et delta

            padic_poly_t Delta;
            padic_poly_init(Delta);
            TechModIncre(Delta,M0,M1,Vr,(N-Nr));

            padic_t deuxexpNr ;
            padic_init(deuxexpNr);
            padic_pow_si(deuxexpNr, deux,Nr,C);

            padic_poly_scalar_mul_padic(cache, Delta,deuxexpNr,C);

            padic_poly_t total;
            padic_poly_init(total);
            padic_poly_add(total,deltar,cache,C);

            fmpz_t d2 ;
            fmpz_init_set_ui(d2, padic_poly_degree(total));
            int deg2;
            deg=fmpz_get_si(d2);

            padic_poly_t totalMod2expN;
            padic_poly_init2(totalMod2expN, deg2 ,N);
            padic_poly_set(totalMod2expN,total,C);
            padic_poly_set(delta,totalMod2expN,C);
            
        }

       

    }


// ---------------- l'algo final

void TeichmullerModulus ( padic_poly_t M, padic_poly_t m, int N )  // on suppose que m est a coef dans Z/2Z, ie dans Z_2 de precision 1
{
    if (N==1)
        {
            padic_poly_set(M,m,C );
            padic_poly_print(M,C);
            printf("\n");
        }
    else
    {
        int Nr = (N>>1)+(N&1); // partie entiere sup de N/2
        padic_poly_t Mr;
        padic_poly_init(Mr);
        TeichmullerModulus(Mr,m,Nr);

        fmpz_t d ;
        fmpz_init_set_ui(d, padic_poly_degree(Mr));
        int deg;
        deg=fmpz_get_si(d);

        // definition de M0

        padic_poly_t M0oX2 ;
        padic_poly_init2(M0oX2,deg+1,(1<<N)); 
        padic_poly_t sum;
        padic_poly_init(sum);
        padic_poly_t MroMX;
        padic_poly_init(MroMX);
        CompomoinsX(MroMX,Mr);
        padic_poly_add(sum, Mr, MroMX, C);
        padic_poly_scalar_mul_padic(M0oX2, sum, un_demi, C);

        padic_poly_t M0;
        padic_poly_init2(M0,deg+1,(1<<N));
        precompoX2(M0,M0oX2);
        padic_poly_clear(M0oX2);

        // definition de M1

        padic_poly_t M1oX2 ;
        padic_poly_init2(M1oX2,deg+1,(1<<N));
        padic_poly_sub(sum, Mr, MroMX, C);
        padic_poly_t cache;
        padic_poly_init(cache);
        padic_poly_scalar_mul_padic(cache, sum, un_demi, C);
        padic_poly_shift_right(M1oX2, cache, 1,C); // la division par X
        padic_poly_clear(sum);


        padic_poly_t M1;
        padic_poly_init2(M1,deg+1,(1<<N));
        precompoX2(M1,M1oX2);
        padic_poly_clear(M1oX2);

        // definition de V
            
        padic_poly_t mult0;
        padic_poly_init(mult0);
        padic_poly_mul(mult0,M0,M0,C);
        padic_poly_t mult1;
        padic_poly_init(mult1);
        padic_poly_mul(mult1,M1,M1,C);
        padic_poly_shift_left(cache, mult1, 1,C); //cache = X*M1*M1

        padic_poly_t sub0;
        padic_poly_init(sub0);
        padic_poly_sub(sub0,mult0,cache,C); // sub0 = M0*M0 - X*M1*M1
        padic_poly_clear(mult0);
        padic_poly_clear(mult1);

        padic_poly_t numerateur;
        padic_poly_init(numerateur);
        padic_poly_sub(numerateur, Mr, sub0,C );
        padic_poly_clear(sub0);

        padic_t un_demiexpNr;
        padic_init(un_demiexpNr);
        padic_pow_si(un_demiexpNr, un_demi, Nr, C);

        padic_poly_t V;
        padic_poly_init2(V,deg,(N-Nr));
        padic_poly_scalar_mul_padic(V, numerateur, un_demiexpNr, C);
        padic_poly_clear(numerateur);

        // definition de delta

        padic_poly_t delta;
        padic_poly_init(delta);
        TechModIncre(delta,M0,M1,V,(N-Nr));

        //definition de M

        padic_t deuxexpNr ;
        padic_init(deuxexpNr);
        padic_pow_si(deuxexpNr, deux,Nr,C);

        padic_poly_scalar_mul_padic(cache, delta,deuxexpNr,C);

        padic_poly_t total;
        padic_poly_init(total);
        padic_poly_add(total,Mr,cache,C);

        fmpz_t d2 ;
        fmpz_init_set_ui(d2, padic_poly_degree(total));
        int deg2;
        deg=fmpz_get_si(d2);

        padic_poly_t totalMod2expN;
        padic_poly_init2(totalMod2expN, deg2 ,N);
        padic_poly_set(totalMod2expN,total,C);
        padic_poly_set(M,totalMod2expN,C);
        padic_poly_print(M,C);
        printf("\n");



    }
    
    
}


//padic_poly_print(P,C);
padic_poly_t test;
padic_poly_init(test);
TeichmullerModulus(test,P,10);
printf("\n");
padic_poly_print(test,C);
flint_cleanup();



}
















