#include "stdio.h"
#include "stdlib.h"

#include "gmp.h"

#include "flint/flint.h"

#include "flint/padic.h"
#include "flint/padic_poly.h"

#include "flint/fmpz.h"
#include "flint/fmpz_poly.h"

#include "../qadic.h"


void CompoXk(padic_poly_t P, padic_poly_t Q, fmpz_t k_conv, padic_ctx_t C) // P(X) prend la valeur Q(X^k)=(Q)o(X^k) 
{
    int N = padic_poly_prec(Q);
    int deg = padic_poly_degree(Q);
    int k =fmpz_get_si(k_conv);

    padic_t padic_temp;
    padic_poly_t padic_poly_temp;

    padic_init2(padic_temp, N);
    padic_poly_init2(padic_poly_temp, (deg + 1)*k, N);

    for (int i = 0; i < deg +1; i = i + 1)
    {
        padic_poly_get_coeff_padic(padic_temp, Q, i, C);
        padic_poly_set_coeff_padic(padic_poly_temp, i*k, padic_temp, C);
    }

    _padic_poly_set_length(P, (deg + 1)*k);
    padic_poly_set(P, padic_poly_temp, C);

    padic_poly_clear(padic_poly_temp);
    padic_clear(padic_temp);
}

void frobSubstitu(qadic_t res, qadic_t x, qadic_ctx_t qC) // res prens la valeur \Sigma(x)
{
    CompoXk(res,x,(*((*qC).C)).p, (*qC).C);
    reduce( res,  qC);
}




// --------------  on veut maintenant pouvoir calculer l'inverse du Frobenius efficacement



void PreCalcul_Cj(qadic_t* Cj , qadic_ctx_t qC) // pour j=0 à p-1, Cj[j] prend la valeur theta^{j*p^{d-1}} puis est réduit selon le context
{   
    // ----------- on définitles constantes p et d en fmpz
    fmpz_t p;
    fmpz_init_set(p,(qC*).p);
    fmpz_t d;
    fmpz_init_set_si(d,padic_poly_degree((qC*).M));


    unsigned int pconv ;
    pconv=fmpz_get_ui(p);
    
    // ----------------on construit p^{d-1}
    unsigned int puiss; 
    fmpz_t puisstemp ;
    fmpz_inti(puisstemp);

    fmpz_t dmoins1; // on construit d-1
    fmpz_init(dmoins1);
    fmpz_sub_si(dmoins1, d, -1);

    fmpz_pow_fmpz(puisstemp, p, dmomins1);
    puiss=fmpz_get_ui(puisstemps);

    // ---------------on construit theta^{p^{d-1}}

    qadic_t tetha;
    qadic_t tethapuiss;
    padic_t un;

    qadic_init(tetha,qC);
    padic_init2(un, 2);
    padic_one(un);
    padic_poly_set_coeff_padic(tetha, 1, un, (*qC).C);

    qadic_init(tethapuiss,qC);
    padic_poly_pow(tethapuiss, tetha, puiss, qC);

    // on construit tour à tour les Cj
    qadic_t tethapuissj;
    padic_poly_init(tethapuissj);
    padic_poly_one(thetapuissj);
    
    qadic_t tempo;
    padic_poly_init(tempo);
    

    for ( unsigned int j = 0; j < pconv; i++) // je fais une boucle naïve pour commencer, où je réduit à chaque fois
    {   
        
        padic_poly_set(Cj[j],thetapuissj,(qC*).C); // Cj[j] prend la bonne valeure

        padic_poly_set(tempo,thetapuissj,(qC*).C);
        padic_poly_mul(tethapuissj,tethapuiss,tempo,(qC*).C); // on augmente j de 1 et on réduit
        qadic_reduce(tethapuissj,qC);
    }

    padic_clear(un);
    qadic_clear(theta);
    qadic_clear(thetapuiss);
    qadic_clear(thetapuissj);
    qadic_clear(tempo);
    
}

void ChoisiCoef( qadic_t res, qadic_t a, int j , qadic_ctx_t qC) // si a=\Sum(a_iX^i) alors res prend la valeur \sum_{pk+j<=d} a_{pk+j}X^k
{
    // on suppose a réduit 
    
    int d=padic_poly_degree((qC*).M);
    int p=fmpz_get_si((qC*).p);
    padic_t temp ;
    padic_init(temp);

    for (int k = 0; p*k+j<d; k++)
    {
        padic_poly_get_coeff_padic(temp,a,p*k+j,(qC*).C);
        padic_poly_set_coeff_padic(res,k,temp,(qC*).C);
    }

    padic_clear(temp);

}

void InvFrob(qadic_t res, qadic_t a, qadic_ctx_t qC) // res prend la valeur \Sigma^{-1}(a)
{
    unsigned int p_ui=fmpz_get_ui((qC*).p);
    
    qadic_t Cj[p_ui];
    PreCalcul_Cj(Cj,qC); // contient tous les Cj(X) dont nous avons besoin
    
    qadic_t temp1;
    qadic_init(temp1,qC);

    qadic_t temp2;
    qadic_init(temp2,qc);

    qadic_t temp3;
    qadic_init(temp3,qc);

    

    for ( int j = 0; j < p_ui ; j++)
    {
        ChoisiCoef(temp1,a,j,qC); // temp1 = \sum_{pk+j<=d} a_{pk+j}X^k
        padic_poly_mul(temp2,temp1,Cj[j],(qC*).C); // temp2 = temp1 * Cj(X)
        padic_poly_set(temp3,res,(qC*).C) ; // temp3 prend la valeur qu'il y a dans res
        padic_poly_add(res,temp2,temp3,(qC*).C) // res =+ temp2
        padic_poly_clear(Cj[j]);
    }
    qadic_reduce(res,qC);
    qadic_clear(temp1);
    qadic_clear(temp2);
    qadic_clear(temp3);
    

}

void main()
{

    qadic_ctx_t qadic_ctx;
    fmpz_t p;
    fmpz_init(p);
    fmpz_set_ui(p, 2);
    
    fmpz_poly_t m;
    padic_poly_t M;
    int n = 8; // Degré de l'extension
    int N = 10; // Précision du contexte
    
    fmpz_poly_init(m);
    padic_poly_init2(M, n + 1, N);

    fmpz_poly_set_coeff_si(m, 0, 1);
    fmpz_poly_set_coeff_si(m, 2, 1);
    fmpz_poly_set_coeff_si(m, 3, 1);
    fmpz_poly_set_coeff_si(m, 4, 1);
    fmpz_poly_set_coeff_si(m, 8, 1);

    _qadic_ctx_init_poly(qadic_ctx, p, m, N, 0, N, PADIC_TERSE);


    qadic_t theta;
    qadic_t res;
    padic_t un;

    qadic_init(theta, qC);    
    padic_init(un);
    padic_set_si(un, 1, (*qC).C);

    padic_poly_set_coeff_padic(theta, 1, un, (*qadic_ctx).C); // il est déja sous forme réduite
    frobSubstitu(res,theta,qC);
    qadic_print(res,qC);
    printf("\n");


    
    
}




