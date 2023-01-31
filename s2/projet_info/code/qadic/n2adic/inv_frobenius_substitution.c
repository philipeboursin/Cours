#include "n2adic.h"

// void n2adic_inv_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx)
// {
// }

// --------------  on veut maintenant pouvoir calculer l'inverse du Frobenius efficacement
// void PreCalcul_Cj(qadic_t* Cj , qadic_ctx_t qC) // pour j=0 à p-1, Cj[j] prend la valeur theta^{j*p^{d-1}} puis est réduit selon le context
// {   
//     // ----------- on définitles constantes p et d en fmpz
//     fmpz_t p;
//     fmpz_init_set(p,(qC*).p);
//     fmpz_t d;
//     fmpz_init_set_si(d,padic_poly_degree((qC*).M));


//     unsigned int pconv ;
//     pconv=fmpz_get_ui(p);
    
//     // ----------------on construit p^{d-1}
//     unsigned int puiss; 
//     fmpz_t puisstemp ;
//     fmpz_inti(puisstemp);

//     fmpz_t dmoins1; // on construit d-1
//     fmpz_init(dmoins1);
//     fmpz_sub_si(dmoins1, d, -1);

//     fmpz_pow_fmpz(puisstemp, p, dmomins1);
//     puiss=fmpz_get_ui(puisstemps);

//     // ---------------on construit theta^{p^{d-1}}

//     qadic_t tetha;
//     qadic_t tethapuiss;
//     padic_t un;

//     qadic_init(tetha,qC);
//     padic_init2(un, 2);
//     padic_one(un);
//     padic_poly_set_coeff_padic(tetha, 1, un, (*qC).C);

//     qadic_init(tethapuiss,qC);
//     padic_poly_pow(tethapuiss, tetha, puiss, qC);

//     // on construit tour à tour les Cj
//     qadic_t tethapuissj;
//     padic_poly_init(tethapuissj);
//     padic_poly_one(thetapuissj);
    
//     qadic_t tempo;
//     padic_poly_init(tempo);
    

//     for ( unsigned int j = 0; j < pconv; i++) // je fais une boucle naïve pour commencer, où je réduit à chaque fois
//     {   
        
//         padic_poly_set(Cj[j],thetapuissj,(qC*).C); // Cj[j] prend la bonne valeure

//         padic_poly_set(tempo,thetapuissj,(qC*).C);
//         padic_poly_mul(tethapuissj,tethapuiss,tempo,(qC*).C); // on augmente j de 1 et on réduit
//         qadic_reduce(tethapuissj,qC);
//     }

//     padic_clear(un);
//     qadic_clear(theta);
//     qadic_clear(thetapuiss);
//     qadic_clear(thetapuissj);
//     qadic_clear(tempo);
    
// }

// void ChoisiCoef( qadic_t res, qadic_t a, int j , qadic_ctx_t qC) // si a=\Sum(a_iX^i) alors res prend la valeur \sum_{pk+j<=d} a_{pk+j}X^k
// {
//     // on suppose a réduit 
    
//     int d=padic_poly_degree((qC*).M);
//     int p=fmpz_get_si((qC*).p);
//     padic_t temp ;
//     padic_init(temp);

//     for (int k = 0; p*k+j<d; k++)
//     {
//         padic_poly_get_coeff_padic(temp,a,p*k+j,(qC*).C);
//         padic_poly_set_coeff_padic(res,k,temp,(qC*).C);
//     }

//     padic_clear(temp);

// }

// void InvFrob(qadic_t res, qadic_t a, qadic_ctx_t qC) // res prend la valeur \Sigma^{-1}(a)
// {
//     unsigned int p_ui=fmpz_get_ui((qC*).p);
    
//     qadic_t Cj[p_ui];
//     PreCalcul_Cj(Cj,qC); // contient tous les Cj(X) dont nous avons besoin
    
//     qadic_t temp1;
//     qadic_init(temp1,qC);

//     qadic_t temp2;
//     qadic_init(temp2,qc);

//     qadic_t temp3;
//     qadic_init(temp3,qc);

    

//     for ( int j = 0; j < p_ui ; j++)
//     {
//         ChoisiCoef(temp1,a,j,qC); // temp1 = \sum_{pk+j<=d} a_{pk+j}X^k
//         padic_poly_mul(temp2,temp1,Cj[j],(qC*).C); // temp2 = temp1 * Cj(X)
//         padic_poly_set(temp3,res,(qC*).C) ; // temp3 prend la valeur qu'il y a dans res
//         padic_poly_add(res,temp2,temp3,(qC*).C) // res =+ temp2
//         padic_poly_clear(Cj[j]);
//     }
//     qadic_reduce(res,qC);
//     qadic_clear(temp1);
//     qadic_clear(temp2);
//     qadic_clear(temp3);
// }