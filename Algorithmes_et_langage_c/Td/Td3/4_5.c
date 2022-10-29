#include<stdio.h>


// Multiplication de polynomes en ui
void poly_print(unsigned int P);
// Affichage d'un polynôme
unsigned int poly_mult(unsigned int P, unsigned int Q);
// Tests de la question 4
void q4();
// Calcul du degré d'un polynôme
int deg(unsigned int P);
// division euclidienne dans F2[X]
void div_euc(unsigned int P, unsigned int Q, unsigned int* B, unsigned int* R);
// Algorithme d'euclide étendu dans F2[X]
void euclide(int a, int b, int* rr, int* u, int* v);
// Tests de la question 5
void q5();


//------ Question 4
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

unsigned int poly_mult(unsigned int P, unsigned int Q)
{
    unsigned int res = 0;
    while (P != 0)
    {
        if (P & 1 == 1) res ^= Q ;
        P = P >> 1;
        Q = Q << 1;
    }
    return res;
}

void q4()
{
    unsigned int P = 0b11;
    unsigned int Q = 0b101;
    unsigned int PQ = poly_mult(P, Q);
    printf("P = ");
    poly_print(P);
    printf(", Q = ");
    poly_print(Q);
    printf(", PQ = ");
    poly_print(PQ);
    printf("\n"); 
}


//------ Question 5
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

void div_euc(unsigned int P, unsigned int Q, unsigned int* B, unsigned int* R)
{
    if (Q == 0)
    {
        printf("Erreur division par 0\n");
    }
    else
    {
        *B = 0;
        int i = deg(P) - deg(Q);
        while (i >= 0)
        {
            P ^= (Q << i);
            *B ^= (1 << i);
            i = deg(P) - deg(Q);
        } 
        *R = P;
    }
}

void euclide(int a, int b, int* rr, int* u, int* v)
{
    int u1 = 1;
    int v1 = 0;
    int u2 = 0;
    int v2 = 1;
    int r;
    int q;
    int bu; //buffer u2
    int bv; //buffer u1
    while (b != 0)
    {
        div_euc(a, b, &q, &r);
        bu = u2;
        bv = v2;
        u2 = u1 ^ poly_mult(q, u2);
        v2 = v1 ^ poly_mult(q, v2);
        a = b;
        b = r;
        u1 = bu;
        v1 = bv;
    }
    *rr = a;
    *u= u1;
    *v = v1;
}

void q5()
{
    unsigned int P = 0;
    printf("%d,%d,%d\n", deg(0), deg(1), deg(0b1000));
    P = 0b101;
    unsigned int Q = 0b10;
    unsigned int B = 0;
    unsigned int R = 0;
    unsigned int U = 0;
    unsigned int V = 0;
    div_euc(P, Q, &B, &R);
    printf("P = ");
    poly_print(P);
    printf(", Q = ");
    poly_print(Q);
    printf(", B = ");
    poly_print(B);
    printf(", R = ");
    poly_print(R);
    printf("\n");

    euclide(P, Q, &R, &U, &V);
    printf("U = ");
    poly_print(U);
    printf(", V = ");
    poly_print(V);
    printf(", R = ");
    poly_print(R);
    printf("\n");
}


//------
int main()
{
    // q4();
    q5();
}