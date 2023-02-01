#include "n2adic.h"


/* Calcule la composition de op1 avec op2 (en tant que polynômes). Utilise l'astuce de Paterson-Stockmeyer. */
// void n2adic_composition(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx)
// {
//     slong prec = n2adic_prec(rop);
//     slong deg = ctx -> deg;
//     slong B = n_sqrt(deg); // Calcule \lfloor \sqrt{d} \rfloor
//     if (B*B != deg) B += 1; // B contient \lceil \sqrt{d} \rceil

//     n2adic_t op1_auxi;
//     n2adic_t op2_auxi;
//     n2adic_t op2_pow_i;
//     n2adic_t tab[B + 1];

//     n2adic_init2(op1_auxi, prec, ctx);
//     n2adic_init2(op2_auxi, prec, ctx);
//     n2adic_init2(op2_pow_i, prec, ctx);
//     n2adic_set(op1_auxi, op1, ctx); // Pour monter op1 à la bonne précision.
//     n2adic_set(op2_auxi, op2, ctx); // Pour monter op2 à la bonne précision
//     n2adic_one(op2_pow_i); // Contiendra op2^i

//     for (slong i = 0; i <= B; i++)
//     {
//         n2adic_init2(tab[i], prec, ctx);
//         n2adic_set(tab[i], op2_pow_i);
//         n2adic_mul(op2_pow_i, op2_pow_i, op2_auxi, ctx); // Calcule op2*(op2^i)
//     }

//     for (slong j = 0, )
// }