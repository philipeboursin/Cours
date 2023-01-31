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
#include "flint/fq.h"

//-------------------- Introduction
/* Ce module permet de faire des calculs sur \mathbb{Q}_{2^d}, en représentant l'extension comme un quotient de \mathbb{Q}_2[X] par le module de Teichmüller M de m \in \mathbb{F}_2[X] un polynôme irréductible.
Cela facilite notamment les calculs de substitution de Frobenius. */


//-------------------- Structure de données
typedef padic_poly_t n2adic_t;

int n2adic_prec(n2adic_t x);

slong n2adic_val(n2adic_t x);


//-------------------- Contexte
typedef struct _n2adic_ctx_t
{
    int prec; // Précision des calculs dans l'extension
    int deg; // Degré de l'extension
    padic_ctx_t ctx; // Contexte p-adique associé au sous-corps de l'extension
    padic_poly_t M; // Polynôme représentant de l'extension
} n2adic_ctx_t[1];

void _n2adic_ctx_init_poly(n2adic_ctx_t n2adic_ctx, fmpz_poly_t m, int prec, slong min, slong max, enum padic_print_mode mode);

void n2adic_ctx_init(n2adic_ctx_t n2adic_ctx, unsigned int deg, int prec, slong min, slong max, enum padic_print_mode mode);

void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C);

void n2adic_ctx_rep(padic_poly_t P, n2adic_ctx_t C);


//-------------------- Gestion de la mémoire
void n2adic_init(n2adic_t x, n2adic_ctx_t n2adic_ctx);

void n2adic_init2(n2adic_t x, int prec, n2adic_ctx_t n2adic_ctx);

void n2adic_clear(n2adic_t x);

void n2adic_ctx_clear(n2adic_ctx_t C);


//-------------------- Assignement
void n2adic_set(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx);

void n2adic_set_padic_poly(n2adic_t rop, padic_poly_t op, n2adic_ctx_t n2adic_ctx);

void n2adic_set_fmpz_poly(n2adic_t rop, fmpz_poly_t op, n2adic_ctx_t n2adic_ctx);

void n2adic_get_fmpz_poly(fmpz_poly_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx);

void n2adic_one(n2adic_t rop);


//-------------------- Randomisation
void n2adic_randtest(n2adic_t x, flint_rand_t state, n2adic_ctx_t ctx);


//-------------------- Opérations arithmétiques
void _padic_poly_div_eucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C);

void n2adic_reduce(n2adic_t x, n2adic_ctx_t C);

void n2adic_add(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

void n2adic_sub(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

void n2adic_mul(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

void n2adic_inv(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx);


//-------------------- Fonctions spéciales
void n2adic_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx);

// void n2adic_inv_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx);

void n2adic_artin_schreier_root(n2adic_t x, n2adic_t alpha, n2adic_t beta, n2adic_t gamma, n2adic_ctx_t ctx);


//-------------------- Misc
void n2adic_print(n2adic_t x, n2adic_ctx_t n2adic_ctx);