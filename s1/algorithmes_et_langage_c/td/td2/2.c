#include<stdio.h>
#include<stdlib.h>


//------ Fonctions auxiliaires
// Exponentiation modulaire
int fast_exp(int x, unsigned int k);
// Calcule le degré d'un polynôme
int deg(unsigned int P);
// Affiche un polynôme de F_2[X]
void poly_print(unsigned int P);
//------ Partie 1
// Initialise les tables d'exponentielles et de logarithmes
void tables_init(unsigned int** exp, unsigned int** log, unsigned int qn);
// Libère les tables d'exponentielles et de logarithmes
void tables_free(unsigned int** exp, unsigned int** log);
// Calcule les tables d'exponentielles et de logarithmes
void tables(unsigned int* exp, unsigned int* log, unsigned int P, unsigned int qn);
// Tests de la partie 1
void q1();
//------ Partie 2
// Addition dans F_{qn} (q = 2)
unsigned int add(unsigned int P, unsigned int Q);
// Multiplication dans F_{qn}
unsigned int prod(unsigned int P, unsigned int Q, unsigned int* exp, unsigned int* log, unsigned int qn);
// Inverse dans F_{qn}
unsigned int inv(unsigned int P, unsigned int* exp, unsigned int* log, unsigned int qn);
// Tests de la partie 2
void q2();
//------ Partie 3
// Initialise une table de cayley
void cayley_table_init(unsigned int*** T, unsigned int qn);
// Libère une table de cayley
void cayley_table_free(unsigned int*** T, unsigned int qn);
// Calcule les tablees d'addition et de multiplication dans F_{2^n}
void cayley_table(unsigned int** plus, unsigned int** times, unsigned int P, unsigned int qn);
// Affiche une table de cayley
void table_print(unsigned int** T, unsigned int qn);
// Tests de la partie 3
void q3();
//------ Partie 4
// Initialise la table de logarithme de Zech
void zech_init(unsigned int** zlog, unsigned int qn);
// Libère la table de logarithme de Zech
void zech_free(unsigned int** zlog);
// Calcul du logarithme de Zech
void zech_log(unsigned int* exp, unsigned int* log, unsigned int* zlog, unsigned int P, unsigned int qn);
// Tests de la question 4
void q4();
//------ Partie 5
// Addition sous forme exp
unsigned int add_exp(unsigned int k, unsigned int l, unsigned int* zlog, unsigned qn);
// Multiplication sous forme exp
unsigned int mult_exp(unsigned int k, unsigned int l, unsigned int qn);
// Inverse sous forme exp
unsigned int inv_exp(unsigned int k, unsigned int qn);
// Calcul des tables de Cayley en utilisant le logarithme de Zech
unsigned int cayley_zech(unsigned int** plus, unsigned int** times, unsigned int P, unsigned int qn);
// 1ere serie de tests de la question 5
void q5_1();
// 2eme serie de tests de la question 5
void q5_2();


// Fonctions auxiliaires
int fast_exp(int x, unsigned int k)
{
    int res = 1;
    int pow = x;
    while (k != 0)
    {
        if (k & 1 == 1)
        {
            res = (res * pow);

        }
        pow = (pow * pow);
        k = k >> 1;
    }
    return res;
}

int deg(unsigned int P)
{
    int i = -1;
    {
        while (P != 0)
        {
            P = P >> 1;
            i++;
        }
    }
    return i;
}

void poly_print(unsigned int P)
{
    if (P == 0) printf("0");
    else
    {
        int b = 0;
        int i = 1;
        if (P & 1 == 1)
        {
            printf("%d", 1);
            b = 1;
        }
        P = P >> 1;
        while (P != 0)
        {
            if (P & 1 == 1) 
            {
                if (b == 0) 
                {
                    printf("X^%d", i);
                    b = 1;
                }
                else printf(" + X^%d", i);
            }
            i++;
            P = P >> 1;
        }
    }
}


//------ Partie 1
void tables_init(unsigned int** exp, unsigned int** log, unsigned int qn)
{
    *exp = (unsigned int*) malloc(qn*sizeof(unsigned int));
    *log = (unsigned int*) malloc(qn*sizeof(unsigned int));
}

void tables_free(unsigned int** exp, unsigned int** log)
{
    free(*exp);
    free(*log);
}

void tables(unsigned int* exp, unsigned int* log, unsigned int P, unsigned int qn)
{

    exp[0] = 1;
    log[1] = 0;
    for (int i = 1; i < qn - 1; i++)
    {
        exp[i] = (exp[i - 1]) << 1;
        if ((exp[i] & qn) != 0)
        {
            exp[i] ^= P;
        }
        log[exp[i]] = i;
    }
    exp[qn - 1] = 0;
    log[0] = qn - 1;
}

void q1()
{
    unsigned int* exp;
    unsigned int* log;
    unsigned int P = 0b1011;
    unsigned int n = deg(P);
    unsigned int qn = fast_exp(2, n);
    tables_init(&exp, &log, qn);
    tables(exp, log, P, qn);
    for (int i = 0; i < qn; i ++)
    {
        printf("i = %d, exp(i) = ", i);
        poly_print(exp[i]);
        printf(", log(exp(i)) = %d\n", log[exp[i]]);
    }
    tables_free(&exp, &log);    
}


//------ Partie 2
unsigned int add(unsigned int P, unsigned int Q)
{
    return P^Q;
}

unsigned int prod(unsigned int P, unsigned int Q, unsigned int* exp, unsigned int* log, unsigned int qn)
{
    if (P == 0 || Q == 0) return 0;
    else return exp[(log[P] + log[Q]) % (qn - 1)];
}

unsigned int inv(unsigned int P, unsigned int* exp, unsigned int* log, unsigned int qn)
{
    return exp[qn - 1 - log[P]]; 
}

void q2()
{
    unsigned int* exp;
    unsigned int* log;
    unsigned int P = 0b1011;
    unsigned int A = 0b10;
    unsigned int B = 0b11;
    unsigned int n = deg(P);
    unsigned int qn = fast_exp(2, n);

    tables_init(&exp, &log, qn);
    tables(exp, log, P, qn);
    
    printf("A = ");
    poly_print(A);
    printf(", B = ");
    poly_print(B);
    printf(", P = ");
    poly_print(P);
    printf("\nA + B = ");
    poly_print(add(A, B));
    printf("\nA*B = ");
    poly_print(prod(A, B, exp, log, qn));
    printf("\nA^{-1} = ");
    poly_print(inv(A, exp, log, qn));
    printf("\n");

    tables_free(&exp, &log);
}


//------ Partie 3
void cayley_table_init(unsigned int*** T, unsigned int qn)
{
    *T = (unsigned int**) malloc(qn*sizeof(unsigned int*));
    for (int i = 0; i < qn; i ++)
    {
        (*T)[i] = (unsigned int*) malloc(qn*sizeof(unsigned int));
    }
}

void cayley_table_free(unsigned int*** T, unsigned int qn)
{
    for (int i = 1; i < qn; i ++) free((*T)[i]);
    free(*T);
}

void cayley_table(unsigned int** plus, unsigned int** times, unsigned int P, unsigned int qn)
{
    unsigned int* exp;
    unsigned int* log;

    tables_init(&exp, &log, qn);
    tables(exp, log, P, qn);

    for (unsigned int i = 0; i < qn; i++)
    {
        for (unsigned int j = 0; j < qn; j++)
        {
            plus[i][j] = add(i, j);
            times[i][j] = prod(i, j, exp, log, qn);
        }
    }

    tables_free(&exp, &log);
}

void table_print(unsigned int** T, unsigned int qn)
{
    for (int i = 0; i < qn; i++)
    {
        for (int j = 0; j < qn; j++)
        {
            printf("%x", T[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void q3()
{
    unsigned int** plus;
    unsigned int** times;
    unsigned int P = 0b1011;
    unsigned int qn = fast_exp(2, deg(P));
    cayley_table_init(&plus, qn);
    cayley_table_init(&times, qn);

    cayley_table(plus, times, P, qn);
    printf("Table d'addition :\n");
    table_print(plus, qn);
    printf("Table de multiplication :\n");
    table_print(times, qn);

    cayley_table_free(&plus, qn);
    cayley_table_free(&times, qn);
}


//------ Partie 4
void zech_init(unsigned int** zlog, unsigned int qn)
{
    *zlog = (unsigned int*) malloc(qn*sizeof(unsigned int));
}

void zech_free(unsigned int** zlog)
{
    free(*zlog);
}

void zech_log(unsigned int* exp, unsigned int* log, unsigned int* zlog, unsigned int P, unsigned int qn)
{
    for (int i = 0; i < qn; i++)
    {
        zlog[i] = log[1^exp[i]];
    }
}

void q4()
{
    unsigned int* exp;
    unsigned int* log;
    unsigned int* zlog;
    unsigned int P = 0b1011;
    unsigned int qn = fast_exp(2, deg(P));

    tables_init(&exp, &log, qn);
    zech_init(&zlog, qn);

    tables(exp, log, P, qn);
    zech_log(exp, log, zlog, P, qn);
    poly_print(exp[zlog[3]]);
    printf("\n");
}


//------ Partie 5
unsigned int add_exp(unsigned int k, unsigned int l, unsigned int* zlog, unsigned qn)
{
    if (k == (qn - 1)) return l;
    else if (l == (qn - 1)) return k;
    else if (k == l) return qn;
    else return (k + zlog[(qn - 1 + l - k) % (qn - 1)]) % (qn - 1);
}

unsigned int mult_exp(unsigned int k, unsigned int l, unsigned int qn)
{
    if (k == (qn - 1) || l == (qn - 1)) return qn;
    else return (k + l) % (qn - 1);
}

unsigned int inv_exp(unsigned int k, unsigned int qn)
{
    return (qn - 1) - (k % (qn - 1));
}

void q5_1()
{
    unsigned int P = 0b1011;
    unsigned int qn = fast_exp(2, deg(P));
    unsigned int* zlog;
    unsigned int* exp;
    unsigned int* log;

    tables_init(&exp, &log, qn);
    zech_init(&zlog, qn);

    tables(exp, log, P, qn);
    zech_log(exp, log, zlog, P, qn);

    printf("%u\n", mult_exp(4, 5, qn));
    printf("%u\n", add_exp(7, 2, zlog, qn));
}

unsigned int cayley_zech(unsigned int** plus, unsigned int** times, unsigned int P, unsigned int qn)
{
    unsigned int* zlog;
    unsigned int* exp;
    unsigned int* log;

    tables_init(&exp, &log, qn);
    zech_init(&zlog, qn);

    tables(exp, log, P, qn);
    zech_log(exp, log, zlog, P, qn);

    for (unsigned int i = 0; i < qn; i++)
    {
        for (unsigned int j = 0; j < qn; j++)
        {
            plus[exp[i]][exp[j]] = exp[add_exp(i, j, zlog, qn)];
            times[exp[i]][exp[j]]  = exp[mult_exp(i, j, qn)];
        }
    }

    tables_free(&exp, &log);
    zech_free(&zlog);
}

void q5_2()
{
    unsigned int** plus;
    unsigned int** times;
    unsigned int P = 0b1011;
    unsigned int qn = fast_exp(2, deg(P));
    cayley_table_init(&plus, qn);
    cayley_table_init(&times, qn);

    cayley_zech(plus, times, P, qn);
    printf("Table d'addition :\n");
    table_print(plus, qn);
    printf("Table de multiplication :\n");
    table_print(times, qn);

    cayley_table_free(&plus, qn);
    cayley_table_free(&times, qn);
}

//------
int main()
{
    // q1();
    // q2();
    // q3();
    // q4();
    // q5_1();
    q5_2();
}