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
#include "flint/ulong_extras.h"


//-------------------- Introduction
/* Soit $p$ un nombre premier et $q = p^d \in \mathbb{Z}$. Ce module permet de faire des calculs sur $\mathbb{Z}_{q}$, en représentant l'extension comme un quotient de $\mathbb{Z}_p[X]$ par un polynôme $M \in \mathbb{F}_2[X]$ irréductible.*/


//-------------------- Structure de données
/* Un élément de $\mathbb{Z}_q$ est la classe d'équivalence d'un élément de $\mathbb{Z}_p[X]$ modulo $M$. On le représente donc par un élément de $\mathbb{Z}_p[X]$, que l'on réduira modulo $M$ tout au long des calculs. On dira qu'il est sous forme réduite s'il est réduit modulo $M$*/

/* Type représentant un élément de $\mathbb{Z}_q$. */
typedef padic_poly_t n2adic_t;

/* Fonction renvoyant la précision à laquelle "x" est représenté. */
slong n2adic_prec(n2adic_t x);

/* Fonction renvoyant la valuation de "x". */
slong n2adic_val(n2adic_t x);


//-------------------- Contexte
/* Un contexte d'entiers $q$-adiques contient les informations nécessaires aux calculs dans $\mathbb{Z}_q$, ainsi que différents éléments précalculés permettant d'accélérer certains calculs. */

/* Différents types de polynômes pouvant représenter l'extension $\mathbb{Q}_q$ de $\mathbb{Q}_p$. */
enum rep_type {TEICHMULLER, SPARSE};

/* Type représentant un contexte d'entiers $q$-adiques. */
typedef struct _n2adic_ctx_t
{
    slong prec; // Précision maximale des calculs dans l'extension, dans le cas où le représentant est calculé à une précision donnée (e.g. module de Teichmuller)
    slong deg; // Degré de l'extension
    enum rep_type type; // Type de représentant
    fmpz_t p; // Nombre premier tel que $p^{deg} = q$
    n2adic_t* C;// Pointeur vers un tableau contenant les éléments $C_j \in Z_q$. Reste null si le type n'est pas TEICHMULLER
    padic_ctx_t pctx; // Contexte $p$-adique associé au sous-corps de l'extension
    padic_poly_t M; // Polynôme représentant de l'extension
} n2adic_ctx_t[1];

/* Procédure permettant d'initialiser un contexte "n2adic_ctx" à partir d'un polynôme "M" $\in \mathbb{Z}_p$ (supposé irréductible), dans un contexte "padic_ctx". La précision maximale de l'extension sera donnée par la précision de "M" si "type == TEICHMULLER". */
void n2adic_ctx_init_padic_poly(n2adic_ctx_t n2adic_ctx, padic_poly_t M, padic_ctx_t padic_ctx, enum rep_type type);

/* Procédure calculant le module de Teichmuller de "m" $\in \mathbb{F}_p[X]$, vu comme un polynôme de $\mathbb{Z}_p[X]$, à précision "N". Le résultat est mis dans "M"". /!\ Ne marche qu'avec $p = 2$ (dans le contexte) /!\ */
void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, slong N, padic_ctx_t C);

/* Procédure permettant d'initialiser un contexte "n2adic_ctx", avec comme représentant le module de Teichmuller de "m" $\in \mathbb{F}_p[X]$ vu comme un polynôme de $\mathbb{Z}[X]$. Les informations "min", "max" et "mode" permettent d'initialiser le contexte $p$-adique dans lequel seront représentés les coefficients des polynômes représentant les éléments de $\mathbb{Z}_q$ (voir padic.h). /!\ Ne fonctionne qu'avec $p = 2$ /!\  */
void _n2adic_ctx_init_teichmuller(n2adic_ctx_t n2adic_ctx, fmpz_poly_t m, slong prec, slong min, slong max, enum padic_print_mode mode);

/* Procédure permettant d'initlaiser un contexte "n2adic_ctx", avec comme un représentant le module de Teichmuller d'un polynôme alétoire pris dans $\mathbb{F}_p[X]$. Les informations "min", "max" et "mode" permettent d'initialiser le contexte $p$-adique dans lequel seront représentés les coefficients des polynômes représentant les éléments de $\mathbb{Z}_q$ (voir padic.h). /!\ Ne fonctionne qu'avec $p = 2$ /!\ */
void n2adic_ctx_init_teichmuller(n2adic_ctx_t n2adic_ctx, slong deg, slong prec, slong min, slong max, enum padic_print_mode mode);

/* Procédure permettant d'initlaiser un contexte "n2adic_ctx", avec comme représentant le relèvememnt creux de "m" $\in \mathbb{F}_p[X]$ vu comme un polynôme de $\mathbb{Z}[X]$. Les informations "min", "max" et "mode" permettent d'initialiser le contexte $p$-adique dans lequel seront représentés les coefficients des polynômes représentant les éléments de $\mathbb{Z}_q$ (voir padic.h). */
void _n2adic_ctx_init(n2adic_ctx_t n2adic_ctx, fmpz_poly_t m, fmpz_t p, slong prec, slong min, slong max, enum padic_print_mode mode);

/* Procédure permettant d'initlaiser un contexte "n2adic_ctx", avec comme un représentant le relèvement creux d'un polynôme alétoire pris dans $\mathbb{F}_p[X]$. Les informations "min", "max" et "mode" permettent d'initialiser le contexte $p$-adique dans lequel seront représentés les coefficients des polynômes représentant les éléments de $\mathbb{Z}_q$ (voir padic.h). */
void n2adic_ctx_init(n2adic_ctx_t n2adic_ctx, fmpz_t p, slong deg, slong prec, slong min, slong max, enum padic_print_mode mode);

/* Procédure permettant de récupérer le représentant d'un contexte d'entiers $q$-adiques "n2adic_ctx_t". Met le résultat dans "P". */
void n2adic_ctx_rep(padic_poly_t P, n2adic_ctx_t ctx);


//-------------------- Gestion de la mémoire

/* Permet d'initialiser la mémoire nécessaire pour un "x" $\in \mathbb{Z}_q$. La précision par défaut est donnée par la précision du contexte "n2adic_ctx". */
void n2adic_init(n2adic_t x, n2adic_ctx_t n2adic_ctx);

/* Permet d'initialiser la mémoire nécessaire opur un "x" $\in \mathbb{Z}_q$, à précision "prec". */
void n2adic_init2(n2adic_t x, slong prec, n2adic_ctx_t n2adic_ctx);

/* Permet de libérer la mémoire allouée pour "x". */
void n2adic_clear(n2adic_t x);

/* Permet de libérer la mémoire allouée pour "ctx" un contexte d'entiers q-adiques. */
void n2adic_ctx_clear(n2adic_ctx_t ctx);


//-------------------- Assignement

/* Met la valeur de "op" dans "rop". */
void n2adic_set(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx);

/* Met dans "rop" le représentant réduit modulo le polynôme représentant $\mathbb{Z}_q$ de "op". */
void n2adic_set_padic_poly(n2adic_t rop, padic_poly_t op, n2adic_ctx_t n2adic_ctx);

/* Met dans "rop" le représentant réduit modulo le polynôme représentant $\mathbb{Z}_q$ de l'inclusion canonique de "op" $\in \mathbb{Z}[X]$ dans $\mathbb{Z}_p[X]$. */
void n2adic_set_fmpz_poly(n2adic_t rop, fmpz_poly_t op, n2adic_ctx_t n2adic_ctx);

/* Met dans rop le relèvement canonique de "op" $\in \mathbb{Z}_q$, vu comme un élément de $\mathbb{Z}_p[X]$ à précision donnée, donc un élément de $(\mathbb{Z}/p^{prec} \mathbb{Z})[X]$. */
void n2adic_get_fmpz_poly(fmpz_poly_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx);

/* Met $1$ dans "rop". */
void n2adic_one(n2adic_t rop);

/* Met $0$ dans "rop". */
void n2adic_zero(n2adic_t rop);


//-------------------- Randomisation

/* Génère un élément de $\mathbb{Z}_q$ aléatoire. Met le résultat dans "x". */
void n2adic_randtest(n2adic_t x, flint_rand_t state, n2adic_ctx_t ctx);


//-------------------- Comparaison

/* Renvoie "1" si et seulement si "x" $=$ "y". */
int n2adic_equal(n2adic_t x, n2adic_t y);

/* Renvoie "1" si et seulement si "x" $= 1$. */
int n2adic_is_one(n2adic_t x);


//-------------------- Opérations arithmétiques
void _padic_poly_div_eucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C);

/* Met sous forme réduite "x" $\in \mathbb{Z}_q$. */
void n2adic_reduce(n2adic_t x, n2adic_ctx_t C);

/* Additionne "op1" et "op2". Met le résultat dans rop. */
void n2adic_add(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

/* Réalise la soustration de "op1" avec "op2". Met le résultat dans "rop". */
void n2adic_sub(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

/* Réalise la multiplication de "op1" avec "op2". Met le résultat dans "rop". */
void n2adic_mul(n2adic_t rop, n2adic_t op1, n2adic_t op2, n2adic_ctx_t ctx);

/* Inverse "op", en supposant qu'il est inversible. Met le résultat dans "rop". */
void n2adic_inv(n2adic_t rop, n2adic_t op, n2adic_ctx_t n2adic_ctx);

/* Met "op" à la puissance "e" dans rop. */
void n2adic_pow(n2adic_t rop, n2adic_t op, fmpz_t e, n2adic_ctx_t ctx);


//-------------------- Fonctions spéciales

/* Réalise la substitution du frobenius en "op", dans l'extension spécifiée par "ctx". Met le résultat dans "rop". */
void n2adic_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx);

/* Réalise la substitution du frobenius inverse en "op", dans l'extension spécifiée par "ctx". Met le résulta dans "rop". */
void n2adic_inv_frobenius_substitution(n2adic_t rop, n2adic_t op, n2adic_ctx_t ctx);

/* Résout l'équation d'Artin-Schreier avec paramètres "alpha", "beta" et "gamma". Met le résultat dans "x". */
void n2adic_artin_schreier_root(n2adic_t x, n2adic_t alpha, n2adic_t beta, n2adic_t gamma, n2adic_ctx_t ctx);


//-------------------- Misc

/* Affiche un "x" de $\mathbb{Z}_q$, représenté comme un élément de $\mathbb{Z}_p[X]$. Les coefficients de ce polynôme (dans $\mathbb{Z}_p$) seront affichés selon le mode spécifié dans le contexte $p$-adique associé à "ctx" ("ctx -> ctxp"). */
void n2adic_print(n2adic_t x, n2adic_ctx_t ctx);