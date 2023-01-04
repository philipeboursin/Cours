#include<stdio.h>
#include<gmp.h>
#include<flint/padic.h>
#include<flint/padic_poly.h>
#include<flint/fmpz.h>

//  ----------------on initialise les premières constantes et le context


void main()
{


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





// on a besoin de pouvoir réduire les polynômes 2-adiques modulo 2^N


padic_poly_t redmod2n( padic_poly_t P, int N ) 
{
    padic_poly_t mod;
    fmpz_t d ;
    fmpz_init_set_ui(d, padic_poly_degree(P));
    int deg;
    deg=fmpz_get_si(d);
    padic_poly_init2(mod, deg+1, N);
    padic_poly_set(mod, P,C);
    return mod; 
}



// on a besoin de construire P(-X) à partir de P(X) 

padic_poly_t CompomoinsX( padic_poly_t P)
{
    padic_poly_t res;
    padic_poly_init(res);

    padic_poly_t moinsX;
    padic_poly_init(moinsX);
    padic_t moinsun;
    padic_init(moinsun);
    padic_t a;
    padic_init(a);
    padic_one(a);
    padic_neg(moinsun,a,C);
    padic_poly_set_coeff_padic(moinsX,1,moinsun, C);


    padic_poly_compose(res, P, moinsX, C);

    return res;
}

// on a besoin de pouvoir definir des polynomes par P(X^2)= ....  

padic_poly_t precompoX2( padic_poly_t P) // on suppose que P est un polynôme ayant pour coefs non nuls que ceux devant des X^{2i}
{
    padic_poly_t res;
    padic_poly_init(res);

    fmpz_t d ;
    fmpz_init_set_ui(d, padic_poly_degree(P));
    int deg;
    deg=fmpz_get_si(d);

    padic_t coefs[deg+1];
    
    for (int i = 0; i < deg+1; i=i+2)
    {
        padic_init(coefs[i]);
        padic_poly_get_coeff_padic(coefs[i], P, i, C);
        padic_poly_set_coeff_padic(res, i/2, coefs[i], C);

    }
    
    return res;

}


// ----------------- l'incrémentation de Teichmuller


padic_poly_t TechModIncre( padic_poly_t M0, padic_poly_t M1, padic_poly_t V, int N)

    {
        if (N==1)
        {
            padic_poly_t delta;
            padic_poly_init(delta);

            padic_poly_t vmod2;
            padic_poly_init(vmod2);
            padic_poly_set(vmod2, redmod2n(V,1),C );

            padic_poly_neg(delta, vmod2, C);
            padic_poly_clear(vmod2);
            return delta;

        }
        else
        {
            int Nr = (N>>1)+(N&1)           ; // partie entiere superieur de N/2
            padic_poly_t deltar;
            padic_poly_init(deltar);
            padic_poly_set(deltar,TechModIncre(M0,M1,V,Nr),C);
            
            fmpz_t d ;
            fmpz_init_set_ui(d, padic_poly_degree(deltar));
            int deg;
            deg=fmpz_get_si(d);

            // definition de delta0

            padic_poly_t delta0oX2 ;
            padic_poly_init2(delta0oX2,deg+1,(1<<N));
            padic_poly_t sum;
            padic_poly_init(sum);
            padic_poly_add(sum, deltar, CompomoinsX(deltar), C);
            padic_poly_scalar_mul_padic(delta0oX2, sum, un_demi, C);

            padic_poly_t delta0;
            padic_poly_init2(delta0,deg+1,(1<<N));
            padic_poly_set(delta0,precompoX2(delta0oX2),C);
            padic_poly_clear(delta0oX2);

            // definition de delta1

            padic_poly_t delta1oX2 ;
            padic_poly_init2(delta1oX2,deg+1,(1<<N));
            padic_poly_sub(sum, deltar, CompomoinsX(deltar), C);
            padic_poly_t cache;
            padic_poly_init(cache);
            padic_poly_scalar_mul_padic(cache, sum, un_demi, C);
            padic_poly_shift_right(delta1oX2, cache, 1,C); // la division par X


            padic_poly_t delta1;
            padic_poly_init2(delta1,deg+1,(1<<N));
            padic_poly_set(delta1,precompoX2(delta1oX2),C);
            padic_poly_clear(delta0oX2);

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
            padic_poly_init2(V,deg,(1<<(N-Nr)));
            padic_poly_scalar_mul_padic(Vr, numerateur, un_demiexpNr, C);
            padic_poly_clear(numerateur);

            //definition de Delta et delta

            padic_poly_t Delta;
            padic_poly_init(Delta);
            padic_poly_set(Delta, TechModIncre(M0,M1,Vr,(N-Nr)),C);

            padic_poly_t delta;
            padic_poly_init2(delta,deg,(1<<N));
            padic_t deuxexpNr ;
            padic_pow_si(deuxexpNr, deux,Nr,C);
            padic_poly_scalar_mul_padic(cache,Delta,deuxexpNr,C);
            padic_poly_add(delta,deltar,cache,C);
            return delta;
        }

       

    }


}
















