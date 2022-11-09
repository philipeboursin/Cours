#include<stdio.h>
#include<stdlib.h>


// Fonctions auxiliaires
// Exponentiation modulaire
int fast_exp(int x, unsigned int k);
// Calcule le degré d'un polynôme
int deg(unsigned int P);
// Affiche un polynôme de F_2[X]
void poly_print(unsigned int P);
//------ Partie 1
// Initialise les tables d'exponentielles et de logarithmes
unsigned int tables_init(unsigned int** exp, unsigned int** log, unsigned int qn);
// Libère les tables d'exponentielles et de logarithmes
unsigned int tables_free(unsigned int** exp, unsigned int** log);
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
// Initialise une table de Cayley
void Cayley_table_init(unsigned int*** T, unsigned int qn);
// Libère une table de Cayley
void Cayley_table_free(unsigned int*** T, unsigned int qn);
// Calcule les tablees d'addition et de multiplication dans F_{2^n}
void Cayley_table(unsigned int** plus, unsigned int** times, unsigned int P, unsigned int qn);
// Affiche une table de Cayley
void table_print(unsigned int** T, unsigned int qn);
// Tests de la partie 3
void q3();


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
unsigned int tables_init(unsigned int** exp, unsigned int** log, unsigned int qn)
{
    *exp = (unsigned int*) malloc(qn*sizeof(unsigned int));
    *log = (unsigned int*) malloc(qn*sizeof(unsigned int));
}

unsigned int tables_free(unsigned int** exp, unsigned int** log)
{
    free(*exp);
    free(*log);
}

unsigned int tables(unsigned int* exp, unsigned int* log, unsigned int P, unsigned int qn)
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
void Cayley_table_init(unsigned int*** T, unsigned int qn)
{
    *T = (unsigned int**) malloc(qn*sizeof(unsigned int*));
    for (int i = 0; i < qn; i ++)
    {
        (*T)[i] = (unsigned int*) malloc(qn*sizeof(unsigned int));
    }
}

void Cayley_table_free(unsigned int*** T, unsigned int qn)
{
    for (int i = 1; i < qn; i ++) free((*T)[i]);
    free(*T);
}

void Cayley_table(unsigned int** plus, unsigned int** times, unsigned int P, unsigned int qn)
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
    Cayley_table_init(&plus, qn);
    Cayley_table_init(&times, qn);

    Cayley_table(plus, times, P, qn);
    printf("Table d'addition :\n");
    table_print(plus, qn);
    printf("Table de multiplication :\n");
    table_print(times, qn);

    Cayley_table_free(&plus, qn);
    Cayley_table_free(&times, qn);
}


//------
int main()
{
    // q1();
    // q2();
    q3();
}