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
typedef padic_poly_t n2adic_t;


//-------------------- Contexte
typedef struct _n2adic_ctx_t
{
    int N; // Précision des calculs dans l'extension
    int n; // Degré de l'extension
    fmpz_t p; // Nombre premier 
    padic_ctx_t C; // Contexte p-adique associé au sous-corps de l'extension
    padic_poly_t M; // Polynôme représentant de l'extension
} n2adic_ctx_t[1];

void _n2adic_ctx_init_poly(n2adic_ctx_t C, fmpz_t p, fmpz_poly_t m, int N, slong min, slong max, enum padic_print_mode mode);

void n2adic_ctx_init(n2adic_ctx_t C, fmpz_t p, unsigned int n, int N, slong min, slong max, enum padic_print_mode mode);

void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C);

void n2adic_ctx_rep(padic_poly_t P, n2adic_ctx_t C);


//-------------------- Gestion de la mémoire
void n2adic_init(n2adic_t x, n2adic_ctx_t n2adic_ctx);

void n2adic_clear(n2adic_t x);

void n2adic_ctx_clear(n2adic_ctx_t C);


//-------------------- Assignement
void n2adic_set_padic_poly(n2adic_t rop, padic_poly_t op, n2adic_ctx_t n2adic_ctx);


//-------------------- Opérations arithmétiques
void _padic_poly_div_eucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C);

void n2adic_reduce(n2adic_t x, n2adic_ctx_t C);

void n2adic_add(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

void n2adic_mul(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);


//-------------------- Misc
void n2adic_print(n2adic_t x, n2adic_ctx_t n2adic_ctx);