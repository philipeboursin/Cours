#include "stdio.h"
#include "stdlib.h"

#include "gmp.h"

#include "flint/flint.h"

#include "flint/padic.h"
#include "flint/padic_poly.h"

#include "flint/fmpz.h"
#include "flint/fmpz_poly.h"

#include "flint/fmpz_mod.h"
#include "flint/fmpz_mod_poly.h"


//-------------------- Structure de données
typedef padic_poly_t qadic_t;


//-------------------- Contexte
typedef struct _qadic_ctx_t
{
    int N; // Précision des calculs dans l'extension
    int n; // Degré de l'extension
    fmpz_t p; // Nombre premier 
    padic_ctx_t C; // Contexte p-adique associé au sous-corps de l'extension
    padic_poly_t M; // Polynôme représentant de l'extension
} qadic_ctx_t[1];

void _qadic_ctx_init_poly(qadic_ctx_t C, fmpz_t p, fmpz_poly_t m, int N, slong min, slong max, enum padic_print_mode mode);

// void qadic_ctx_init(qadic_ctx_t C, fmpz_t p, unsigned int n, slong min, slong max, enum padic_print_mode mode);

void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C);

void qadic_ctx_rep(padic_poly_t P, qadic_ctx_t C);


//-------------------- Gestion de la mémoire
void qadic_init(qadic_t x, qadic_ctx_t qadic_ctx);

void qadic_clear(qadic_t x);

void qadic_ctx_clear(qadic_ctx_t C);


//-------------------- Assignement
void qadic_set_padic_poly(qadic_t rop, padic_poly_t op, qadic_ctx_t qadic_ctx);


//-------------------- Opérations arithmétiques
void qadic_reduce(qadic_t x, qadic_ctx_t C);

void qadic_add(qadic_t rop, qadic_t op1, qadic_t op2, qadic_ctx_t ctx);


//-------------------- Misc
void qadic_print(qadic_t x, qadic_ctx_t qadic_ctx);