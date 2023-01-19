//#include "qadic.h"

//------
// void CoefRenv(padic_poly_t P, padic_poly_t Q, padic_ctx_t C) // Procédure qui transforme P en un polynôme dont les coefficients sont ceux de Q renversés
// {
//     int deg = padic_poly_degree(Q);
//     int N = padic_poly_prec(Q);

//     padic_poly_t R;
//     padic_t padic_cache;
//     padic_poly_init2(R, deg, N);
//     padic_init2(padic_cache, N);

//     for (int i = 0; i < deg + 1; i++)
//     {
//         padic_poly_get_coeff_padic(padic_cache, Q, i, C);
//         padic_poly_set_coeff_padic(R, deg-i, padic_cache, C);
//     }

//     padic_poly_set(P, R, C);
//     padic_clear(padic_cache);
// }

// void _padic_poly_div_eucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C)
// {
//     int degA = padic_poly_degree(A);
//     int degB = padic_poly_degree(B);
//     int N = padic_poly_prec(B);

//     if (degA < degB)
//     {
//         padic_poly_set(R, A, C);
//         padic_poly_zero(Q);
//     }
//     else
//     {
//         int n = degA - degB + 1;

//         padic_poly_t P1; //polynômes variables caches
//         padic_poly_t P2;

//         padic_poly_init2(P1, degA, N);
//         padic_poly_init2(P2, degA, N);

//         CoefRenv(P2, B, C);
//         padic_poly_inv_series(P2, P2, n, C);

//         CoefRenv(P1, A, C);
//         padic_poly_mul(P2, P1, P2, C);
//         _padic_poly_set_length(P2, n);
//         CoefRenv(Q, P2, C);  

//         padic_poly_mul(P1, B, Q, C);
//         padic_poly_sub(R, A, P1, C);

//         padic_poly_clear(P1);
//         padic_poly_clear(P2);
//     }
// }

// void qadic_reduce(qadic_t x, qadic_ctx_t C)
// {
//     qadic_t y;
//     padic_poly_init2(y, padic_poly_degree(x), padic_poly_prec(x));
//     _padic_poly_div_eucl(x, (*C).M, x, (*C).C);
//     padic_poly_reduce(x, (*C).C);
// }

// void qadic_add(qadic_t rop, qadic_t op1, qadic_t op2, qadic_ctx_t ctx)
// {
//     padic_poly_add(rop, op1, op2, ctc.C);
//     qadic_reduce(rop, ctx);
// }