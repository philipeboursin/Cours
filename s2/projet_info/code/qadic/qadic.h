#include "stdio.h"
#include "stdlib.h"

#include "gmp.h"

#include "flint/flint.h"

#include "flint/padic.h"
#include "flint/padic_poly.h"

#include "flint/fmpz.h"
#include "flint/fmpz_poly.h"


//------ Introduction :


//------ Structure de données
// Type représentant les éléments de \mathbb{Q}_q
typedef padic_poly_t qadic_t;


//------ Contexte
// Contexte q-adique : comprend un contexte p-adique et un polynôme représentant l'extension q-adique 
typedef struct _qadic_ctx_t
{
    int N; // Précision des calculs dans l'extension
    int n; // Degré de l'extension
    padic_ctx_t C; // Contexte p-adique associé au sous-corps de l'extension
    padic_poly_t M; // Polynôme représentant de l'extension
} qadic_ctx_t[1];


// Initialise un contexte pour une extension q-adique de Qp, en prenant comme polynôme représentant l'extension le relèvement de Teichmuller de m
void _qadic_ctx_init_poly(qadic_ctx_t C, fmpz_t p, fmpz_poly_t m, int N, slong min, slong max, enum padic_print_mode mode);

// Initialise un contexte pour une extension q-adique de Qp, en prenant comme polynôme représentant l'extension le relèvement de Teichmuller d'un polynôme irréductible de \mathbb{F}_p[X] creux
// void qadic_ctx_init(qadic_ctx_t C, fmpz_t p, unsigned int n, slong min, slong max, enum padic_print_mode mode);

// Teichmuller modulus
void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C);

// Met dans P le représentant de l'extension associée au contexte C
void qadic_ctx_rep(padic_poly_t P, qadic_ctx_t C);


//------ Gestion de la mémoire
void qadic_init(qadic_t x, qadic_ctx_t qadic_ctx);

void qadic_clear(qadic_t x);

// PAS ENCORE IMPLEMENTE
void qadic_ctx_clear(qadic_ctx_t C);



//------ Opérations arithmétiques
// void qadic_add(qadic_t rop, qadic_t op1, qadic_t op2, qadic_ctc_t ctx);